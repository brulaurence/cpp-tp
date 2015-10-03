#define Entete_Facture  ""\
"╔══════════════════════════════════════════════════════════════════════════════╗\n"\
"║                                                                              ║\n"\
"║                                COMPAGNIE MICRO-TEMPO                         ║\n"\
"║                                                                              ║\n"\
"║ Numéro du client  : %04d                                                     ║\n"\
"║ Numéro du vendeur : %04d                                                     ║\n"\
"║                                                                              ║\n"\
"║                                                                              ║\n"\
"║     Numéro     Prix       Quantité     Quantité    Montant    Remarque       ║\n"\
"║     Produit    Unitaire   Commandée    Livrée                                ║\n"\
"║                                                                              ║\n"\
""
#define Ligne_Article  ""\
"║      %03d       %6.2f         %2d         %2d        %7.2f¤       %2s         ║\n"\
""
#define  Ligne_NI  ""\
"║      %03d                                                          NI         ║\n"\
""
#define  Ligne_ND  ""\
"║      %03d       %6.2f         %2d          0                       ND         ║\n"\
""
#define Final_Facture  ""\
"║                                                                              ║\n"\
"║                                 Sous-total       : %7.2f¤                  ║\n"\
"║                                 Escompte         : %7.2f¤                  ║\n"\
"║                                 Total avant taxe : %7.2f¤                  ║\n"\
"║                                 Tps              : %7.2f¤                  ║\n"\
"║                                 TVQ              : %7.2f¤                  ║\n"\
"║                                                                              ║\n"\
"║                                 Total            : %7.2f¤                  ║\n"\
"║                                                                              ║\n"\
"║ND : quantité non disponible                                                  ║\n"\
"║NI : numéro invalide                                                          ║\n"\
"║LI : Livraison incomplète                                                     ║\n"\
"╚══════════════════════════════════════════════════════════════════════════════╝\n"\
""

#define Entete_Stock  ""\
"╔══════════════════════════════════════════════════════════════════════════════╗\n"\
"║                                                                              ║\n"\
"║                             LISTE DES PRODUITS                               ║\n"\
"║                          PAR ORDRE DE DESCRIPTION                            ║\n"\
"║                                                                              ║\n"\
"║    NUMÉRO                 DESCRIPTION          QUANTITÉ      STOCK           ║\n"\
"║    PRODUIT                                     VENDUE        ÉPUISÉ          ║\n"\
""
#define Ligne_Stock  ""\
"║                                                                              ║\n"\
"║      %03d           %25s     %-2d           %3s            ║\n"\
""
#define Final_Stock  ""\
"║                                                                              ║\n"\
"╚══════════════════════════════════════════════════════════════════════════════╝\n"\
""
