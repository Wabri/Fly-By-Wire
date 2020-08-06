
// Dichiarazione funzioni
// <tipo> <nome> ([<tipo-parametro>[,...]]);

int test(const char *yolo, ...);

long test2(int);

void test3(void);

void test4(); // dichiarazione della solita fuzione test3, ma incorretta secondo lo standard ANSI

// Implementazione funzione
// <tipo> <nome> ([<tipo> <parametro>[,...]]) {
//  <istruzione>; ...
// }

int prodotto (int x, int y) {
    return x*y;
}

static void funzione_accessibile_solo_da_questo_file() {
    // ...
}

static int accumulatore(int contatore) {
    static int sIContatore = 0;
    sIContatore += contatore;
    return sIContatore;
}

