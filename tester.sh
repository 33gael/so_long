#!/bin/bash

# ==========================================
# CONFIGURATION
# ==========================================
PROG="./so_long"
MAP_DIR="maps_test_auto"
LOG_FILE="valgrind_output.log"
OUT_FILE="prog_output.txt"

# Force Valgrind à être en Anglais pour le grep
export LANG=C

# Couleurs
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
NC='\033[0m'

# ==========================================
# FONCTIONS UTILITAIRES
# ==========================================

print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}       $1       ${NC}"
    echo -e "${BLUE}========================================${NC}"
}

check_leaks() {
    # 1. Vérification basique si le log est vide
    if [ ! -s "$LOG_FILE" ]; then
         echo -e "${YELLOW}[VALGRIND FAIL]${NC} (Log vide)"
         return
    fi

    # 2. Cherche le message de succès (Pas de fuites)
    if grep -a -q "All heap blocks were freed" "$LOG_FILE"; then
        LOST_BYTES="0"
    else
        # 3. Tentative d'extraction des "definitely lost"
        # On cherche la ligne, on prend la dernière occurrence (résumé), on extrait le chiffre
        # Exemple ligne: "==123==    definitely lost: 40 bytes in 1 blocks"
        LOST_LINE=$(grep -a "definitely lost:" "$LOG_FILE" | tail -n 1)
        
        if [[ -z "$LOST_LINE" ]]; then
            LOST_BYTES="" # Échec du parsing
        else
            # Extraction avec sed: on garde uniquement les chiffres après "lost:"
            LOST_BYTES=$(echo "$LOST_LINE" | sed -E 's/.*definitely lost:[^0-9]*([0-9,]+).*/\1/' | tr -d ',')
        fi
    fi

    # 4. Affichage des résultats
    if [[ "$LOST_BYTES" == "0" ]]; then
        echo -n -e "${GREEN}[LEAKS OK]${NC} "
    elif [[ -z "$LOST_BYTES" ]]; then
        # C'est ici que tu avais l'erreur. 
        # On affiche le log pour comprendre ce qui se passe.
        echo -e "${RED}[LEAKS ?]${NC} (Parsing error)"
        echo -e "${YELLOW}--- DEBUG: CONTENU DU LOG VALGRIND ---${NC}"
        cat "$LOG_FILE"
        echo -e "${YELLOW}--- FIN DEBUG ---${NC}"
        return # On arrête l'affichage pour ce test
    else
        echo -n -e "${RED}[LEAKS KO: ${LOST_BYTES} bytes]${NC} "
    fi

    # 5. Analyse des erreurs mémoire (Invalid read, etc.)
    ERRORS_LINE=$(grep -a "ERROR SUMMARY:" "$LOG_FILE" | tail -n 1)
    ERRORS_COUNT=$(echo "$ERRORS_LINE" | sed -E 's/.*ERROR SUMMARY:[^0-9]*([0-9,]+).*/\1/' | tr -d ',')

    if [[ "$ERRORS_COUNT" == "0" ]]; then
        echo -e "${GREEN}[MEM OK]${NC}"
    else
        echo -e "${RED}[MEM ERRORS: ${ERRORS_COUNT}]${NC}"
        # Affiche la première erreur spécifique
        DETAIL=$(grep -a -E "Invalid|Uninitialised|mismatched|overlap" "$LOG_FILE" | head -n 1 | sed 's/==.*== //')
        if [ ! -z "$DETAIL" ]; then
            echo -e "${YELLOW}   -> Detail: $DETAIL${NC}"
        fi
    fi
}

run_test() {
    TEST_NAME="$1"
    MAP_FILE="$2"
    EXPECTED="$3" # "Error" ou "Success"
    ARGS="$4" 

    if [ -z "$ARGS" ]; then
        CMD_ARGS="$MAP_FILE"
    else
        CMD_ARGS="$ARGS"
    fi

    echo -n -e "TEST: $TEST_NAME ... "

    # Exécution avec Valgrind
    # On redirige stdout ET stderr
    valgrind --leak-check=full --show-leak-kinds=all --suppressions=/home/zaak/Documents/Code/42/so_long/libs/MacroLibX/valgrind.supp --track-origins=yes $PROG $CMD_ARGS > "$OUT_FILE" 2> "$LOG_FILE"
    RET=$?
    
    # Analyse du résultat (Sans lire dans une variable bash pour éviter les null bytes)
    if [ "$EXPECTED" == "Error" ]; then
        # grep -a traite le fichier comme du texte même s'il y a du binaire
        if grep -a -q "Error" "$OUT_FILE"; then
            echo -n -e "${GREEN}[MSG OK]${NC} "
        else
            echo -n -e "${RED}[MSG KO]${NC} "
            # On affiche un petit bout de la sortie pour comprendre
            preview=$(head -n 1 "$OUT_FILE")
            echo "(Attendu: Error, Reçu: $preview)"
        fi
        check_leaks
    elif [ "$EXPECTED" == "Success" ]; then
        if [ $RET -eq 0 ] || [ $RET -eq 130 ]; then # 130 = fermé par signal (CTRL+C ou kill)
            echo -n -e "${GREEN}[RUN OK]${NC} "
        else
            echo -n -e "${RED}[RUN CRASH (Code $RET)]${NC} "
        fi
        check_leaks
    fi
}

# ==========================================
# SETUP
# ==========================================
if [ ! -f "$PROG" ]; then
    echo -e "${RED}Erreur : Compile d'abord avec make !${NC}"
    exit 1
fi

rm -rf $MAP_DIR
mkdir -p $MAP_DIR

# ==========================================
# 1. TESTS ARGUMENTS & FICHIERS
# ==========================================
print_header "TESTS ARGUMENTS & FICHIERS"

run_test "Aucun argument" "" "Error" " "
run_test "Trop d'arguments" "" "Error" "map.ber map2.ber"
run_test "Fichier inexistant" "ghost.ber" "Error"

touch "$MAP_DIR/wrong_ext.txt"
run_test "Mauvaise extension (.txt)" "$MAP_DIR/wrong_ext.txt" "Error"

touch "$MAP_DIR/hidden.ber"
run_test "Fichier caché (.ber)" "$MAP_DIR/hidden.ber" "Error"

touch "$MAP_DIR/no_read.ber"
chmod 000 "$MAP_DIR/no_read.ber"
run_test "Permission refusée" "$MAP_DIR/no_read.ber" "Error"
chmod 777 "$MAP_DIR/no_read.ber"

mkdir "$MAP_DIR/dossier.ber"
run_test "Dossier au lieu de fichier" "$MAP_DIR/dossier.ber" "Error"

# ==========================================
# 2. TESTS CONTENU DU FICHIER
# ==========================================
print_header "TESTS CONTENU / FORME"

touch "$MAP_DIR/empty.ber"
run_test "Fichier vide (0 octets)" "$MAP_DIR/empty.ber" "Error"

echo "" > "$MAP_DIR/just_nl.ber"
run_test "Fichier 1 octet (NL)" "$MAP_DIR/just_nl.ber" "Error"

echo -e "111\n101\n11" > "$MAP_DIR/rect.ber"
run_test "Non rectangulaire" "$MAP_DIR/rect.ber" "Error"

echo -e "111\n101\n111\n" > "$MAP_DIR/nl_end.ber"
run_test "Newline à la fin" "$MAP_DIR/nl_end.ber" "Error" 

echo -e "111\n101\n\n111" > "$MAP_DIR/nl_middle.ber"
run_test "Ligne vide au milieu" "$MAP_DIR/nl_middle.ber" "Error"

echo -e "111\n1 1\n111" > "$MAP_DIR/space.ber"
run_test "Espace dans la map" "$MAP_DIR/space.ber" "Error"

echo -e "111\n1\t1\n111" > "$MAP_DIR/tab.ber"
run_test "Tabulation dans la map" "$MAP_DIR/tab.ber" "Error"

echo -e "111\n1X1\n111" > "$MAP_DIR/badchar.ber"
run_test "Caractère interdit (X)" "$MAP_DIR/badchar.ber" "Error"

# ==========================================
# 3. TESTS MURS
# ==========================================
print_header "TESTS MURS"

echo -e "01111\n10001\n11111" > "$MAP_DIR/wall_up.ber"
run_test "Mur haut troué" "$MAP_DIR/wall_up.ber" "Error"

echo -e "11111\n10001\n11101" > "$MAP_DIR/wall_down.ber"
run_test "Mur bas troué" "$MAP_DIR/wall_down.ber" "Error"

echo -e "11111\n00001\n11111" > "$MAP_DIR/wall_left.ber"
run_test "Mur gauche troué" "$MAP_DIR/wall_left.ber" "Error"

echo -e "11111\n10000\n11111" > "$MAP_DIR/wall_right.ber"
run_test "Mur droit troué" "$MAP_DIR/wall_right.ber" "Error"

# ==========================================
# 4. TESTS COMPOSANTS (P, E, C)
# ==========================================
print_header "TESTS COMPOSANTS"

echo -e "11111\n100C1\n11111" > "$MAP_DIR/no_p.ber"
run_test "Pas de Joueur (P)" "$MAP_DIR/no_p.ber" "Error"

echo -e "11111\n1P0C1\n11111" > "$MAP_DIR/no_e.ber"
run_test "Pas de Sortie (E)" "$MAP_DIR/no_e.ber" "Error"

echo -e "11111\n1P0E1\n11111" > "$MAP_DIR/no_c.ber"
run_test "Pas de Collectible (C)" "$MAP_DIR/no_c.ber" "Error"

echo -e "11111\n1PPC1\n1E001\n11111" > "$MAP_DIR/double_p.ber"
run_test "Double Joueur" "$MAP_DIR/double_p.ber" "Error"

echo -e "11111\n1PCC1\n1E0E1\n11111" > "$MAP_DIR/double_e.ber"
run_test "Double Sortie" "$MAP_DIR/double_e.ber" "Error"

# ==========================================
# 5. TESTS FLOOD FILL (Chemins)
# ==========================================
print_header "TESTS FLOOD FILL"

echo -e "1111111\n1111111\n1P01001\n1001E01\n1001001\n1111111\n100C001\n1111111" > "$MAP_DIR/no_path_e.ber"
run_test "Sortie Inaccessible" "$MAP_DIR/no_path_e.ber" "Error"

echo -e "1111111\n1111111\n1P00001\n1001001\n1001C01\n1111111\n100E001\n1111111" > "$MAP_DIR/no_path_c.ber"
run_test "Collectible Inaccessible" "$MAP_DIR/no_path_c.ber" "Error"

# ==========================================
# 6. TEST MAP VALIDE (INTERACTIF)
# ==========================================
print_header "TEST MAP VALIDE (INTERACTIF)"
echo -e "${CYAN}ATTENTION : Une fenêtre va s'ouvrir.${NC}"
echo -e "${CYAN}Appuie sur ESC ou CROIX ROUGE pour fermer proprement.${NC}"
echo "Lancement dans 3 secondes..."
sleep 3

echo -e "111111\n1P0C01\n1000E1\n111111" > "$MAP_DIR/valid.ber"
run_test "Map Valide" "$MAP_DIR/valid.ber" "Success"

# ==========================================
# CLEANUP
# ==========================================
print_header "FIN DES TESTS"
rm -f "$OUT_FILE" "$LOG_FILE"
rm -rf $MAP_DIR

