#include <iostream>

#include <fstream>

#include <string>

#include <iomanip>

#include <ctime>

#include <cctype>

#include <sstream>

#include <limits>

#include <unistd.h>

#include<conio.h>

#include <cstdlib>

#include<chrono>

#include<thread>

#include<windows.h>


using namespace std;



class compteBancaire {

private:

    int numeroCompte;

    double solde;

    string nomPrenom;

    string typeCompte;

    string dateDerniereModification;

    string dateSuppression;



public:


 string getCurrentDate() {

        time_t now = time(0);

        struct tm* ltm = localtime(&now);

        char buffer[80];

        strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);

        return string(buffer);

    }
    
void setColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	}
    // Créer un compte
     
        void creeCompte() {           

        ifstream fichier("comptes_bancaires.txt"); // Nouveau nom du fichier

        if (!fichier) {

            cout << "Erreur d\'ouverture du fichier !" << endl;

            return;

        }else{



        // Générer le numéro de compte automatiquement

        int dernierNumeroCompte = 0;

        string ligne;



        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            dernierNumeroCompte = numeroCompte;

        }



        numeroCompte = dernierNumeroCompte + 1;

        fichier.close();



        cin.ignore();  

        cout << "Creation d\'un nouveau compte..." << endl;

        cout << "\n\t Numero de compte generer automatiquement : " << numeroCompte << endl;



        cout << "\n\t Entrez votre Nom et Prenom:\t" << endl;

        getline(cin, nomPrenom);  



        //	cout << "\n\t\t Entrez un Solde de Depart:\t" << endl;

      // cin >> solde;



        cout << "\n\t Entrez le type du compte (Epargne, Bloque, Courant, Entreprise) :" << endl;

                while (!(cin >> typeCompte))
				 {
                   cout << "Erreur de saisie. Veuillez entrer un chiffre : "<<endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                    }
        
        
		do{
			
					cout<<"\n Solde initial(mini 5000 FCFA) : ";
					
						while (!(cin >> solde))
						 {
                          cout << "Erreur de saisie. Veuillez entrer un chiffre : "<<endl;
                          cin.clear(); 
                         cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                          }
					if(solde<5000){
						
						cout<<"\n \t Erreur : le solde initial doit etre d'au moins 5000 FCFA.veuillez reessayer:\t";
					}
					
				}while(solde<5000);
			



        cout << "|  |  |  |  |  |  |Compte creer avec succes !|  |  |  |  |  |  |" << endl;
        float estBloque;
        cout<<"\n";
        cout << "Compte numero " << numeroCompte << endl;

        cout << "Titulaire : " << nomPrenom << endl;

        cout << "Solde : " << fixed << setprecision(2) << solde << endl;
        
        cout << "Type de compte : " << typeCompte << endl;
        
        cout<<" \n|Statut : "<<("Actif")<<endl;
        
/*
         if(typeCompte == "\nEpargne")
		 {
		//cout<<"\nTaux d'interet:"<<tauxInteret<<"%"<<endl;
		
	}else if(typeCompte == "\nBloque"){
		
		cout<<"\nDuree de blocage : "<<duree<<"mois"<<endl;
		
	}else if(typeCompte == "\nEntreprise"){
		
		cout<<"\nLimite de credit:"<<limite<<"FCFA"<<endl;
	}
*/


        ofstream fichierSortie("comptes_bancaires.txt", ios::app);

        if (!fichierSortie) {

            cout << "Erreur d'ouverture du fichier !" << endl;

            return;

        }



        fichierSortie << numeroCompte << endl;

        fichierSortie << nomPrenom << endl;

        fichierSortie << solde << endl;

        fichierSortie << typeCompte << endl;



        fichierSortie.close();

    }
}



   void afficherTousLesComptes() {

    ifstream fichier("comptes_bancaires.txt");

    

    if (!fichier.is_open()) {

        cout << "Erreur lors de l'ouverture du fichier." << endl;

        return;

    }else{



    // En-têtes de la table

    cout << "============================= Liste des comptes =============================" << endl;

    cout << " Numero| Titulaire            | Solde      | Type de compte  | " << endl;

    cout << "-----------------------------------------------------------------------------" << endl;



    int numeroCompte;

    string nomPrenom;

    double solde;

    string typeCompte;

    



    // Lecture des comptes et affichage

    while (fichier >> numeroCompte) {

        fichier.ignore(); // Ignore le saut de ligne après le numéro de compte

        getline(fichier, nomPrenom); // Lit le nom et prénom

        fichier >> solde; // Lit le solde

        fichier.ignore(); // Ignore le saut de ligne après le solde

        getline(fichier, typeCompte); // Lit le type de compte



        // Affichage des données dans le format requis

        cout <<"\t"<< numeroCompte << " | " << left << setw(20) << nomPrenom << " | " 

             << right << setw(10) << solde << " | " 

             << setw(15) << typeCompte << " | " 

             << dateDerniereModification <<"\n"<< endl;

    }



    fichier.close();

    cout << "===============================================================================" << endl;
     cout<<"\n";
     	}
}






    // Afficher un compte spécifique

    void afficherCompteSpecifique(int numeroCompteRecherche) {

        ifstream fichier("comptes_bancaires.txt");

        if (!fichier.is_open()) {

            cout << "Erreur lors de l\'ouverture du fichier." << endl;

            return;

        }else{
	



        bool compteTrouve = false;

        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte == numeroCompteRecherche) {

                compteTrouve = true;

                cout << "============================== Compte trouver ==============================" << endl;

                cout << "Numero de compte : " << numeroCompte << endl;

                cout << "Titulaire : " << nomPrenom << endl;

                cout << "Solde : " << fixed << setprecision(2) << solde << endl;

                cout << "Type de compte : " << typeCompte << endl;

                cout << "===========================================================================" << endl;

                break;

            }

        }



        if (!compteTrouve) {

            cout << "\n\t compte avec le numero specifier non  trouver" << endl;

        }



        fichier.close();
        	}

    }



    // Supprimer un compte

    void supprimerCompte(int numeroCompteASupprimer) {

    	ofstream fichierCorbeille("corbeille.txt", ios::app);

        ifstream fichier("comptes_bancaires.txt");

        if (!fichier.is_open()) {

            cout << "Erreur lors de l\'ouverture du fichier." << endl;

            return;

        }else{
	



        ofstream fichierTemp("comptes_temp.txt");

        if (!fichierTemp.is_open()) {

            cout << "Erreur lors de la creation du fichier temporaire." << endl;

            return;

        }



        bool compteTrouve = false;

        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte != numeroCompteASupprimer) {

                fichierTemp << numeroCompte << endl;

                fichierTemp << nomPrenom << endl;

                fichierTemp << solde << endl;

                fichierTemp << typeCompte << endl;

            } else {

                compteTrouve = true;

                fichierCorbeille << numeroCompte << endl;

                fichierCorbeille << nomPrenom << endl;

                fichierCorbeille << solde << endl;

                fichierCorbeille << typeCompte << endl;

                fichierCorbeille << dateSuppression << endl;

                

            }

        }



        fichier.close();

        fichierTemp.close();



        if (compteTrouve) {

            remove("comptes_bancaires.txt");

            rename("comptes_temp.txt", "comptes_bancaires.txt");
         setColor(11);
            cout << "\n\t compte  supprimer avec succes!" << endl;

        } else {

            cout << "\n\t Le numero de compte specifier n'existe pas !" << endl;

            remove("comptes_temp.txt");

        }
         setColor(7);
         	}
    }



   void modifierCompte(int numeroCompteAModifier)
    {
    ifstream fichier("comptes_bancaires.txt");
    ofstream fichierTemp("comptes_temp.txt");

    if (!fichier.is_open() || !fichierTemp.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return;
    }else{
    
    bool compteTrouve = false;

    while (fichier >> numeroCompte) {

        fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte); // Lit la date de la dernière modification
        
        if (numeroCompte == numeroCompteAModifier)
		 {
            compteTrouve = true;
            cout<<"\n";
            cout << "Compte trouver " << endl;
            cout << "\n\t Nom et Prenom : " << nomPrenom << endl;
            cout << "\n\t Type de compte : " << typeCompte << endl;
            cout << "\n\t Solde : " << solde << endl;
            int choixModification;
            cout << "\t\tQue souhaitez-vous modifier ?" << endl;
            cout<<"\n";
            cout << "\n\t\t 1. Modifier le Nom/Prenom:\t" << endl;
            cout << "\n\t\t 2. Modifier le type de compte:\t" << endl;
            cout << "\n\t\tEntrez votre choix : ";;
             while (!(cin >>choixModification))
			  {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
            cin.ignore();  // pour vider le tampon de saisie
            
            switch (choixModification) {

                case 1:
                    cout << "\n\tEntrez le nouveau Nom et Prenom : ";
                    getline(cin, nomPrenom);
                    cout << "\n\t Nom et Prenom modifier avec succes !" << endl;
                    break;
                case 2:
                    cout << "Entrez le nouveau type de compte (epargne, bloquer, courant) : ";
                    getline(cin, typeCompte);
                    setColor(11);
                    cout << "Type de compte modifier avec succes !" << endl;
                     setColor(7);
                    break;
                default:
                    cout << "Choix invalide !" << endl;
            }
            fichierTemp << numeroCompte << endl;
		    fichierTemp << nomPrenom << endl;
		    fichierTemp << solde << endl;
		    fichierTemp << typeCompte << endl;
             /*Mettre à jour la date de la dernière modification
            time_t now = time(0);
            struct tm *ltm = localtime(&now);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
            dateDerniereModification = buffer;*/
        }else{
        	// Écriture dans le fichier temporaire
        	fichierTemp << numeroCompte << endl;
	        fichierTemp << nomPrenom << endl;
	        fichierTemp << solde << endl;
	        fichierTemp << typeCompte << endl;	
		}
    }

    fichier.close();
    fichierTemp.close();

    if (compteTrouve)
	 {
       remove("comptes_bancaires.txt"); // Supprime le fichier original
       
        rename("comptes_temp.txt", "comptes_bancaires.txt"); // Renomme le fichier temporaire
    } else {
        cout << "\n\t Le numero de compte specifier  non trouver!" << endl;
        
        remove("comptes_temp.txt"); // Supprime le fichier temporaire si le compte n'a pas été trouvé
    }
    
	}

}





    // Effectuer un versement

    void effectuerVersement(int numeroCompteVersement, double montant) {

        ifstream fichier("comptes_bancaires.txt");

        ofstream fichierTemp("comptes_temp.txt");



        if (!fichier.is_open() || !fichierTemp.is_open()) {

            cout << "Erreur lors de l'ouverture du fichier." << endl;

            return;

        }else{



        bool compteTrouve = false;

        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte == numeroCompteVersement) {

                compteTrouve = true;
                
                  if( montant>0){
                  	
                solde += montant; // Ajout du montant au solde

                cout << "\n\t Le versement de " << montant << " effectuer avec succes sur le compte " << numeroCompte << endl;
             }
               else{
               	cout<<"\n\t Invalide! le montant doit etre positif > 0"<<endl;
			   }
            }



            fichierTemp << numeroCompte << endl;

            fichierTemp << nomPrenom << endl;

            fichierTemp << solde << endl;

            fichierTemp << typeCompte << endl;

        }



        fichier.close();

        fichierTemp.close();



        if (compteTrouve) {

            remove("comptes_bancaires.txt");

            rename("comptes_temp.txt", "comptes_bancaires.txt");

        } else {

            cout << "\n\t numero de compte specifier non trouver!" << endl;

            remove("comptes_temp.txt");

        }
        }

    }



    // Effectuer un retrait

    void retirerSomme(int numeroCompteRetrait, double montant) {

        ifstream fichier("comptes_bancaires.txt");

        ofstream fichierTemp("comptes_temp.txt");



        if (!fichier.is_open() || !fichierTemp.is_open()) {

            cout << "Erreur lors de l\'ouverture du fichier." << endl;

            return;

        }else{
		



        bool compteTrouve = false;

        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte == numeroCompteRetrait) {

                compteTrouve = true;

               if(montant>0){
			  
                if (solde >= montant) {
				   
                    solde -= montant; // Déduction du montant du solde

                    cout << "\n\t Le retrait de " << montant << "  effectuer avec succes sur le compte " << numeroCompte << endl;

                } else {

                    cout << "\n\t Fonds insuffisants pour effectuer le retrait!" << endl;

                }
                 }else
                   {
                   	cout<<"\n\t\t invalide! le montant doit etre positif > 0"<<endl;
				   }

            }



            fichierTemp << numeroCompte << endl;

            fichierTemp << nomPrenom << endl;

            fichierTemp << solde << endl;

            fichierTemp << typeCompte << endl;

        }



        fichier.close();

        fichierTemp.close();



        if (compteTrouve) {

            remove("comptes_bancaires.txt");

            rename("comptes_temp.txt", "comptes_bancaires.txt");

        } else {

            cout << "\n\t  numero de compte specifier non trouver" << endl;

            remove("comptes_temp.txt");

        }
        }

    }



    // Effectuer un virement

    void effectuerVirement(int numeroCompteSource, int numeroCompteDest, double montant) {

        ifstream fichier("comptes_bancaires.txt");

        ofstream fichierTemp("comptes_temp.txt");



        if (!fichier.is_open() || !fichierTemp.is_open()) {

            cout << "Erreur lors de l\'ouverture du fichier." << endl;

            return;

        }else{



        bool compteSourceTrouve = false, compteDestTrouve = false;

        double soldeSource, soldeDest;

        string nomPrenomSource, nomPrenomDest, typeCompteSource, typeCompteDest;



        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte == numeroCompteSource) {

                compteSourceTrouve = true;
                 
                 if(solde>0){
				 
                soldeSource = solde;
                }else{
                	cout<<"\n\t le solde doit etre positif > 0";
				}
                nomPrenomSource = nomPrenom;

                typeCompteSource = typeCompte;

            } else if (numeroCompte == numeroCompteDest) {

                compteDestTrouve = true;

                 if(solde>0){
                 	
                soldeDest = solde;

                nomPrenomDest = nomPrenom;

                typeCompteDest = typeCompte;
                
            }else{
                	cout<<"\n\t le solde doit etre positif > 0";
				}
            }



            fichierTemp << numeroCompte << endl;

            fichierTemp << nomPrenom << endl;

            fichierTemp << solde << endl;

            fichierTemp << typeCompte << endl;

        }



        if (compteSourceTrouve && compteDestTrouve) {

            if (soldeSource >= montant) {

                // Effectuer le virement
                 if(montant>0){

                soldeSource -= montant;

                soldeDest += montant;
                
               }else
			    {
               	cout<<"\n\t Invalide! le montant doit etre positif > 0";
			    }
                         
                         
              cout<<"[";
              setColor(11);
	         for( int i = 0;i<=50;i++){
		     cout<<"#"<<flush;
		   
		     this_thread::sleep_for(chrono::milliseconds(50));
		     }
	       cout<<"] Completed!"<<endl;
         setColor(7);
         // Mise à jour des comptes

               
            } else {
                remove("comptes_bancaires.txt");

                rename("comptes_temp.txt", "comptes_bancaires.txt");


             setColor(11);
                cout << "\n\t Le virement de " << montant << " effectuer avec succes de :\n" << nomPrenomSource

                     << " vers " << nomPrenomDest << endl;

                cout << "\n\t Fonds insuffisants pour effectuer le virement." << endl;

            }

        } else {

            cout << "\n\t L\'un des comptes specifier n\'a pas ete trouver !" << endl;

        }

          setColor(7);

        fichier.close();

        fichierTemp.close();
        
       	}

    }



    // Ajouter un compte à la corbeille

    void ajouterACorbeille(int numeroCompteASupprimer) {

        ifstream fichier("comptes_bancaires.txt");

        ofstream fichierCorbeille("corbeille.txt", ios::app);



        if (!fichier.is_open() || !fichierCorbeille.is_open()) {

            cout << "Erreur lors de l'ouverture du fichier." << endl;

            return;

        }else{



        bool compteTrouve = false;

        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte == numeroCompteASupprimer) {

                compteTrouve = true;

                dateSuppression = getCurrentDate(); // Enregistre la date de suppression

                fichierCorbeille << numeroCompte << endl;

                fichierCorbeille << nomPrenom << endl;

                fichierCorbeille << solde << endl;

                fichierCorbeille << typeCompte << endl;

                fichierCorbeille << dateSuppression << endl;

            } else {

                // Écrire le reste des comptes dans le fichier original

                fichierCorbeille << numeroCompte << endl;

                fichierCorbeille << nomPrenom << endl;

                fichierCorbeille << solde << endl;

                fichierCorbeille << typeCompte << endl;

            }

        }



        fichier.close();

        fichierCorbeille.close();



        if (compteTrouve) {
setColor(11);
            cout << "\n\t compte supprimer et deplacer vers la corbeille." << endl;

        } else {

            cout << "\n\t Le numero de compte specifer n\'existe pas." << endl;

        }
setColor(7);
}

    }


    // Récupérer un compte de la corbeille

    void recupererCompteDeLaCorbeille(int numeroCompteASauver) {

        ifstream fichierCorbeille("corbeille.txt");

        ofstream fichierTemp("corbeille_temp.txt");
        
		ofstream fichier("comptes_bancaires.txt", ios::app);


        if (!fichierCorbeille.is_open() || !fichierTemp.is_open()) {

            cout << "Erreur lors de l\'ouverture des fichiers." << endl;

            return;

        }else{



        bool compteTrouve = false;

        string dateSuppressionTemp;

        while (fichierCorbeille >> numeroCompte) {

            fichierCorbeille.ignore();

            getline(fichierCorbeille, nomPrenom);

            fichierCorbeille >> solde;

            fichierCorbeille.ignore();

            getline(fichierCorbeille, typeCompte);

            getline(fichierCorbeille, dateSuppressionTemp);



            if (numeroCompte == numeroCompteASauver) {

                compteTrouve = true;

                // Vérifier si la suppression date de moins de 30 jours

                struct tm lastDeletion = {0};

                int annee, mois, jour;

                sscanf(dateSuppressionTemp.c_str(), "%d-%d-%d", &annee, &mois, &jour);



                lastDeletion.tm_year = annee - 1900;

                lastDeletion.tm_mon = mois - 1;

                lastDeletion.tm_mday = jour;



                time_t t = time(0);

                double secondsDiff = difftime(t, mktime(&lastDeletion));

                double daysDiff = secondsDiff / (60 * 60 * 24); // Nombre de jours depuis la suppression



                if (daysDiff <= 30) {

                    // Récupérer le compte si moins de 30 jours

                    fichier << numeroCompte << endl;

                    fichier << nomPrenom << endl;

                    fichier << solde << endl;

                    fichier << typeCompte << endl;
                    
                   	setColor(11);
                    cout << "\n\t\t Compte recuperer avec succes!" << endl;
                   	
                } else {

                    cout << "\n\t  compte supprimer depuis plus de 30 jours et ne peut pas ETRE RECUPERER!" << endl;
                  setColor(7);
                }                                     

            } else {

                fichierTemp << numeroCompte << endl;

                fichierTemp << nomPrenom << endl;

                fichierTemp << solde << endl;

                fichierTemp << typeCompte << endl;

            }

        }



        fichierCorbeille.close();

        fichierTemp.close();



        if (compteTrouve) {

            remove("corbeille.txt");

            rename("corbeille_temp.txt", "corbeille.txt");

        } else {

            cout << "\n\t compte specifier non trouver dans la corbeille." << endl;

            remove("comptes_temp.txt");

        }

    }   
	
	}                                            



    // Vider la corbeille si plus de 30 jours

    void viderCorbeilleSiNecessaire() {

        ifstream fichierCorbeille("corbeille.txt");

        ofstream fichierTemp("corbeille_temp.txt");



        if (!fichierCorbeille.is_open() || !fichierTemp.is_open()) {

            cout << "Erreur lors de l'ouverture des fichiers." << endl;

            return;

        }else{



        string dateSuppressionTemp;

        while (fichierCorbeille >> numeroCompte) {

            fichierCorbeille.ignore();

            getline(fichierCorbeille, nomPrenom);

            fichierCorbeille >> solde;

            fichierCorbeille.ignore();

            getline(fichierCorbeille, typeCompte);

            getline(fichierCorbeille, dateSuppressionTemp);



            struct tm lastDeletion = {0};

            int annee, mois, jour;

            sscanf(dateSuppressionTemp.c_str(), "%d-%d-%d", &annee, &mois, &jour);



            lastDeletion.tm_year = annee - 1900;

            lastDeletion.tm_mon = mois - 1;

            lastDeletion.tm_mday = jour;



            time_t t = time(0);

            double secondsDiff = difftime(t, mktime(&lastDeletion));

            double daysDiff = secondsDiff / (60 * 60 * 24); // Nombre de jours depuis la suppression



            if (daysDiff <= 30) {

                // Garder le compte

                fichierTemp << numeroCompte << endl;

                fichierTemp << nomPrenom << endl;

                fichierTemp << solde << endl;

                fichierTemp << typeCompte << endl;

                fichierTemp << dateSuppressionTemp << endl;

            }

        }



        fichierCorbeille.close();

        fichierTemp.close();

        remove("corbeille.txt");

        rename("corbeille_temp.txt", "corbeille.txt");
        
        }

    }

    

    // Fonction afficher corbeille

    void afficherCorbeille(){

    	ifstream fichier("corbeille.txt");

    

    if (!fichier.is_open()) {

        cout << "Erreur lors de l'ouverture du fichier." << endl;

        return;

    }else{
    	



    // En-têtes de la table

    cout << "============================= Liste des comptes =============================" << endl;

    cout << "Numero de compte | Titulaire               | Solde       | Type de compte | " << endl;

    cout << "-----------------------------------------------------------------------------" << endl;



    int numeroCompte;

    string nomPrenom;

    double solde;

    string typeCompte;

    



    // Lecture des comptes et affichage

    while (fichier >> numeroCompte) {

        fichier.ignore(); // Ignore le saut de ligne après le numéro de compte

        getline(fichier, nomPrenom); // Lit le nom et prénom

        fichier >> solde; // Lit le solde

        fichier.ignore(); // Ignore le saut de ligne après le solde

        getline(fichier, typeCompte); // Lit le type de compte



        // Affichage des données dans le format requis

        cout << numeroCompte << " | " << left << setw(20) << nomPrenom << " | " 

             << right << setw(10) << solde << " | " 

             << setw(15) << typeCompte << " | " 

             << dateDerniereModification << endl;

    }



    fichier.close();

    cout << "===============================================================================" << endl;

    	}	

	}
	
	
	
	
    // Effectuer un transfert

    void transfert(int numeroCompteSource, int numeroCompteDest, double montant) {

        ifstream fichier("comptes_bancaires.txt");

        ofstream fichierTemp("comptes_temp.txt");



        if (!fichier.is_open() || !fichierTemp.is_open()) {

            cout << "Erreur lors de l\'ouverture du fichier." << endl;

            return;

        }else{
	



        bool compteSourceTrouve = false, compteDestTrouve = false;

        double soldeSource, soldeDest;

        string nomPrenomSource, nomPrenomDest, typeCompteSource, typeCompteDest;



        while (fichier >> numeroCompte) {

            fichier.ignore();

            getline(fichier, nomPrenom);

            fichier >> solde;

            fichier.ignore();

            getline(fichier, typeCompte);



            if (numeroCompte == numeroCompteSource) {

                compteSourceTrouve = true;
                 
                 if(solde>0){
				 
                soldeSource = solde;
                }else{
                	cout<<"\n\t le solde doit etre positif > 0";
				}
                nomPrenomSource = nomPrenom;

                typeCompteSource = typeCompte;

            } else if (numeroCompte == numeroCompteDest) {

                compteDestTrouve = true;

                 if(solde>0){
                 	
                soldeDest = solde;

                nomPrenomDest = nomPrenom;

                typeCompteDest = typeCompte;
                
            }else{
                	cout<<"\n\t le solde doit etre positif > 0";
				}
            }



            fichierTemp << numeroCompte << endl;

            fichierTemp << nomPrenom << endl;

            fichierTemp << solde << endl;

            fichierTemp << typeCompte << endl;

        }



        if (compteSourceTrouve && compteDestTrouve) {

            if (soldeSource >= montant) {

                // Effectuer le virement
                 if(montant>0){

                soldeSource -= montant;

                soldeDest += montant;
                
               }else
			    {
               	cout<<"\n\t Invalide! le montant doit etre positif > 0";
			    }
                         
                         
              cout<<"[";
              setColor(11);
	         for( int i = 0;i<=50;i++){
		     cout<<"#"<<flush;
		   
		     this_thread::sleep_for(chrono::milliseconds(50));
		     }
	       cout<<"] Completed!"<<endl;
         setColor(7);
         // Mise à jour des comptes

               
            } else {
                remove("comptes_bancaires.txt");

                rename("comptes_temp.txt", "comptes_bancaires.txt");


             setColor(11);
                cout << "\n\t L\'envoie de " << montant <<"EUR"<< " effectuer avec succes de :\n" << nomPrenomSource

                     << " vers " << nomPrenomDest << endl;

                cout << "\n\t Fonds insuffisants pour effectuer le virement." << endl;

            }

        } else {

            cout << "\n\t L\'un des comptes specifier n\'a pas ete trouver !" << endl;

        }

          setColor(7);

        fichier.close();

        fichierTemp.close();
        
        }

    }



};

void setColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	}
	
	
void menu()


{
	 
   int i,n,choix,val;
   
	//Get the current time
	auto now=chrono::system_clock::now();
	time_t currentTime=chrono::system_clock::to_time_t(now);
	//convert to local time structure
	tm*localTime=localtime(&currentTime);
	//clear the console( depends on the operating system)
	//ifndef _WIN32
	system("cls");//for windows
	//#endif
	
	
	//display with colors
	setColor(14);//yellow
	
    cout<<"\t\t\t\t***************************"<<endl;
    cout<<"\t\t\t\t*   CURRENT DATE & TIME   *"<<endl;
	cout<<"\t\t\t\t***************************"<<endl;
	
	setColor(11);//ligth blue
    cout<<"\t\t\t\t\t\t\t\t\t\t\t*******************"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t\t Date: "
    <<put_time(localTime,"%d-%m-%Y")//day-month-year format
    <<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t\t*******************"<<endl;
    
	setColor(10);//ligth green  
    cout<<"*****************"<<endl;
    cout<<" Time: " 
	<<put_time(localTime,"%H:%M:%S")//Hour:Minutes:Seconds
	<<endl;
		
	setColor(15);//reset to default(white)
	cout<<"*****************"<<endl;
	//pause for (1) second before refreshing
	this_thread::sleep_for(chrono::seconds(1));
	
   setColor(14);	  
    cout<<"\n";
    
            cout<<"\n\t\t<><><><<<<<<<>>>>>>>>>>>>>BIENVENUE SUR NOTRE BANQUE<<<<<<<<<<<<>>>>>>>>><><><>\n\n";
            cout<<"\n\t\t************************ <><><>MENU OPERATIONS<><><>*****************************";
            cout<<"\n\t\t--------------------------------------------------------------------------------";
            cout<<"\n\t\t\t\t  ||   1.Gestion des Comptes      ||"<<"\n";
			cout<<"\n\t\t\t\t  ||   2.transaction des Comptes  ||"<<"\n";
			cout<<"\n\t\t\t\t  ||   3.Quitter le programme     ||"<<"\n";
			cout<<"\t\t---------------------------------------------------------------------------------";
			cout<<"\n\t\t****************************<><><><><><><><><>*******************************\n";
			 while (!(cin >> choix)) {
            cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             setColor(7);
              }
            //choix=controlsaisie();
            system("cls");
           
       do
       {
            
            switch(choix)
            {
            	{
				
            case 1:
            	setColor(3);
                cout<<"\n";
                cout<<"\n";
                cout<<"\t**************************** <><><> SOUS MENU OPERATIONS<><><>*************************\n";
	            	cout<<"\n\n\n";
                	do{
                		cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++";
	                	cout<<"\n\t\t\t\t\t| Menu de gestion des Comptes |\n";
	                	cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++";
	                	cout<<"\n\n";
	                	cout<<"\t------------------------------------------------------------------------------------";
		                cout<<"\n\t |\t\t 1.Ajouter un compte       ||"; cout<<"\t  5.Afficher tous les comptes     |"<<endl;
		                cout<<"\t------------------------------------------------------------------------------------";
		                cout<<"\n\t |\t\t 2.Supprimer un compte     ||";cout<<"\t  6.Afficher la Corbeille         |"<<endl;
		                cout<<"\t------------------------------------------------------------------------------------";
		                cout<<"\n\t |\t\t 3.Modifier un compte      ||";cout<<"\t  7.Transfert d\'Argent            |"<<endl;
		                cout<<"\t------------------------------------------------------------------------------------";
		                cout<<"\n\t |\t\t 4.Restaurer un compte     ||";cout<<"\t  8.Quitter le sous-menu          |";
		                cout<<"\n\t-----------------------------------------------------------------------------------";
	                     cout<<"\n";      	
		       cout<<"\n\t**************************************<><><><><><><><>***************************************"<<"\n";
	              	cout<<"\n\t Votre Choix :\t "<<endl;
	              		setColor(7);
		
	           	  while (!(cin >> choix)) {
                  cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre  : "<<endl;
                   cin.clear(); 
                  cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
              }
               	system("cls");
               	
		       compteBancaire  compte;
		switch(choix){
			case 1:
				cout<<"\n\t\t\t***************************************************";
				cout<<"\n\t\t\t\t   >      CREATION DE COMPTE     << "<<endl;
				cout<<"\n\t\t\t***************************************************";
			    cout<<"\n\n";

                            compte.creeCompte();
			  
				break;
				
				case 2:
					
				cout<<"\n\t\t\t***************************************************";
				cout<<"\n\t\t\t\t   >>      SUPPRESSION DE COMPTE     << "<<endl;
				cout<<"\n\t\t\t*******************************************************";
				cout<<"\n\n";
				         
					int numeroCompteASupprimer,choix;

                            cout << "Entrez le numero de compte a supprimer : ";

                            //cin >> numeroCompteASupprimer;
                             while (!(cin >> numeroCompteASupprimer)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                                	setColor(11);
                          cout<<"\t\t----------------------------------------------------------"<<endl;
		 	              cout<<"\t\t Etes-Vous sur! de Vouloir Supprimer ce Compte ?"<<endl;
		 	              cout<<" \n\t\t\t      0 : oui   ||    1 : non"<<endl;
		                  cout<<"\n\t\t---------------------------------------------------------"<<endl;
		                	while (!(cin >> choix)) {
                          cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                             cin.clear(); 
                          cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                            }
		 	
		 	                 if(choix==0)
			                  {
			                  	cout<<"\n\n\t\t\t\t| SUPPRESSION |\n\t\t\t\t";
					
					           	cout<<"\n\t\t  En cours"<<endl;
					           	for(int i=1; i<3; i++)
					            	{
						        	cout<<"\t\t...";
						         	sleep(2);
						          }
		 	                   compte.supprimerCompte(numeroCompteASupprimer);
		 	                     	setColor(7);
		 	                     }else if(choix==1)
			                   {
		 	                      	return(menu());
			                   }

                            
						
					
					break;
					
					case 3:
						cout<<"\n\t\t\t***************************************************";
				cout<<"\n\t\t\t\t   >>      MODIFICATION DE COMPTE     << "<<endl;
				cout<<"\n\t\t\t**********************************************************";
					cout<<"\n\n";
					
					 int numeroCompteAModifier;

                            cout << "Entrez le numero de compte a modifier : ";

                            //cin >> numeroCompteAModifier;
                             while (!(cin >> numeroCompteAModifier)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                            

                            compte.modifierCompte(numeroCompteAModifier);

                   
						break;
						
						case 4:
							cout<<"\n\t\t\t***************************************************";
			             	cout<<"\n\t\t\t\t   >>      RESTAURATION DE COMPTE     << "<<endl;
			            	cout<<"\n\t\t\t***************************************************";
			            		cout<<"\n\n";
			            		
			            		int numeroCompteASauver;

                            cout << "\n\t Entrez le numero de compte a restaurer : ";

                            //cin >> numeroCompteASauver;
                             while (!(cin >> numeroCompteASauver)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                                
                                	setColor(11);
                          cout<<"\t\t----------------------------------------------------------"<<endl;
		 	              cout<<"\t\t Etes-Vous sur! de Vouloir Restaurer ce Compte ?"<<endl;
		 	              cout<<" \n\t\t\t      0 : oui   ||    1 : non"<<endl;
		                  cout<<"\n\t\t---------------------------------------------------------"<<endl;
		                	while (!(cin >> choix)) {
                          cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                             cin.clear(); 
                          cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                            }
		 	
		 	                 if(choix==0)
			                  {
			                  	cout<<"\n\n\t\t\t\t| RESTAURATION |\n\t\t\t\t";
					
					           	cout<<"\n\t\t  En cours"<<endl;
					           	for(int i=1; i<3; i++)
					            	{
						        	cout<<"\t\t...";
						         	sleep(2);
						          }
		 	                   compte.recupererCompteDeLaCorbeille(numeroCompteASauver);
		 	                     	setColor(7);
		 	                     }else if(choix==1)
			                   {
		 	                      	return(menu());
			                   }
                            
								
							
						case 5:
							cout<<"\n\t\t\t***************************************************";
				            cout<<"\n\t\t\t\t   >>     AFFICHAGE DES COMPTES     << "<<endl;
				            cout<<"\n\t\t\t***************************************************";
						    cout<<"\n\n";
						    
						     compte.afficherTousLesComptes();
							
							break;
							
							case 6:
								cout<<"\n\t\t\t***************************************************";
			                   	cout<<"\n\t\t\t\t   >>         CORBEILLE          << "<<endl;
			                 	cout<<"\n\t\t\t***************************************************";
			                 	cout<<"\n\n";
						
                             	 compte.afficherCorbeille();
								
								break;
								
								case 7:
								    cout<<"\n\t\t Moneygram Transfert  ";
											cout<<"\n\t\t ";
											
								int numeroCompteSource, numeroCompteDest,tr;  double montant;		               		
                               
                               cout<<"\n";
                            cout << "\n\t Entrez le numero de l\'Expediteur : ";

                           
                             while (!(cin >>numeroCompteSource)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }

                            cout << "\n\t Entrez le numero de compte Recepteur : ";

                            //cin >> numeroCompteDest;
                            while (!(cin >>numeroCompteDest)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                            
                            cout << "\n\t\t Entrez le montant a transferer :\t";

                            //cin >> montant;
                            while (!(cin >> montant)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                                 cout<<"\n\t\t\t\t | Envoie en cours...|";
                                 cout<<"\n veuillez Patienter quelques instants";
                                   cout<<"\n";
                                    cout<<"[";
                                    	setColor(11);
	                                for( int i = 0;i<=50;i++){
		                           cout<<"#"<<flush;
		   
		                          this_thread::sleep_for(chrono::milliseconds(50));
		                            }
	                              cout<<"] Completed!"<<endl;
                                   setColor(7);
                           
						    compte.transfert(numeroCompteSource, numeroCompteDest, montant);
                                    cout << "\n\t\tMontant transferer : " << montant ;
                                    
                                    setColor(11);
                            cout<<"\n\t\tVoulez-vous faire un autre transfert ?"<<endl;
                          cout<<"\t\t----------------------------------------------------------"<<endl;
		 	              cout<<"\t\t  1. Westerunion";cout<<"\t 3. Moneygram"<<endl;
		 	              cout<<"\t\t  2.   Ria";      cout<<"\t  4. My Nita"<<endl;
		 	              cout<<"\t\t----------------------------------------------------------"<<endl;
		 	              cout<<" \n\t\t\t      0 : oui   ||    1 : non"<<endl;
		                  cout<<"\n\t\t---------------------------------------------------------"<<endl;
		                	while (!(cin >> tr)) {
                          cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                             cin.clear(); 
                          cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                            }
		 	
		 	                 if(tr==0)
			                  {
			                  	
		 	                   compte.transfert(numeroCompteSource, numeroCompteDest, montant);
                                    cout << "\n\t\tMontant transferer : " << montant << " EUR\n";
		 	                     	setColor(7);
		 	                     }else if(choix==1)
			                   {
		 	                      	return(menu());
			                   }
                                    
											break;
								
								case 8:
								
									menu();
									break;
									default:
										cout<<"Choix invalide! veuillez reessayer:\t";
										break;
		}
	}while(choix!=8);
                   
                break;
		   
            case 2:
                
                cout<<"\n";
                do{
                            cout<<"************************ <><><> SOUS MENU OPERATIONS<><><>*************************\n\n";
                            cout<<"\n\n";
                            cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++";
	                	    cout<<"\n\t\t\t\t\t| Menu Transaction des Comptes |\n";
	                	    cout<<"\t\t\t\t++++++++++++++++++++++++++++++++++++++++++++";
                            cout<<"\n\n";
	                	    cout<<"\t---------------------------------------------------------------------------------";
                          	cout<<"\n\t|\t 1.Verser une somme           |"; cout<<"\t\t 4.Affiche un  compte           |"<<endl;
                          	cout<<"\t---------------------------------------------------------------------------------";
                          	cout<<"\n\t|\t 2.Retirer une somme          |";cout<<"\t\t 5.Afficher tous les comptes    |"<<endl;
                          	cout<<"\t---------------------------------------------------------------------------------";
			                cout<<"\n\t|\t3.Virement d\'une somme        |";cout<<"\t\t6.Quitter le sous-menu          |"<<endl;
			                cout<<"\t---------------------------------------------------------------------------------";
			                cout<<"\n\n";
			                cout<<"\n\**********************************<><><><><><><><>***************************************\n";
			                cout<<"\n\tEntrer votre choix\t:";
			                while (!(cin >> choix)) {
                           cout << "Erreur de saisie !\n\n Veuillez entrer un chiffre : ";
                             cin.clear(); 
                             cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                               }
			                //choix=controlsaisie();
			                system("cls");
			                compteBancaire compte;
			                if(choix==6){
			                	return (menu());
							}else if(choix==1){
								cout<<"\n\t\t***************************************************";
								cout<<"\n\t\t   >>         Versement     << "<<endl;
								cout<<"\n\t\t***************************************************";
								cout<<"\n\n";
								
							int numeroCompteVersement;

                            double montant;

                            cout << "\n\t Entrez le numero de compte pour le versement : ";

                            //cin >> numeroCompteVersement;
                            while (!(cin >> numeroCompteVersement)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }

                            cout << "\n\t Entrez le montant a verser : ";

                           // cin >> montant;
                            while (!(cin >> montant)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }

                            compte.effectuerVersement(numeroCompteVersement, montant);

									  
							}else if(choix==2){
								cout<<"\n\t\t***************************************************";
								cout<<"\n\t\t\t    >>        Retrait      << "<<endl;;
								cout<<"\n\t\t***************************************************";
								    cout<<"\n\n";
								    
								    
                            int numeroCompteARetirer;

                           double montant;
                            string typeCompte,Bloque;

                            cout << "\n\t Entrez le numero de compte : ";
                           
                            while (!(cin >>numeroCompteARetirer)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                    

                            cout << "\n\tEntrez le montant a retirer : ";

                            //cin >> montant;
                            while (!(cin >> montant)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }

                            compte.retirerSomme(numeroCompteARetirer, montant);
                            
							}else if(choix==3){
								cout<<"\n\t\t***************************************************";
								 cout<<"\n\t\t\t\t >>       Virerement Bancaire     <<"<<endl;
								 cout<<"\n\t\t***************************************************";
								cout<<"\n\n";
								
							 int numeroCompteSource, numeroCompteDest;

                            double montant;

                            cout << "\n\t Entrez le numero de compte source : ";

                            //cin >> numeroCompteSource;
                             while (!(cin >>numeroCompteSource)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }

                            cout << "\n\t Entrez le numero de compte destination : ";

                            //cin >> numeroCompteDest;
                            while (!(cin >>numeroCompteDest)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }

                            cout << "\n\t\t Entrez le montant a virer : ";

                            //cin >> montant;
                            while (!(cin >> montant)) {
                             cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                               cin.clear(); 
                               cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                }
                                 cout<<"\n\t\t\t\t | Virement en cours...|";
                                 cout<<"\n veuillez Patienter quelques instants";
                                   cout<<"\n";
                                    cout<<"[";
                                    	setColor(11);
	                                for( int i = 0;i<=50;i++){
		                           cout<<"#"<<flush;
		   
		                          this_thread::sleep_for(chrono::milliseconds(50));
		                            }
	                              cout<<"] Completed!"<<endl;
                                   setColor(7);
                            compte.effectuerVirement(numeroCompteSource, numeroCompteDest, montant);

							}else if(choix==4){
								cout<<"\n\t\t***************************************************";
								cout<<"\n\t\t\t\t >>    Affichage d\'un  compte     <<"<<endl;
								cout<<"\n\t\t***************************************************";
									cout<<"\n\n";
									
									 int numeroCompte;

                               cout << "Entrez le numero du compte a afficher : ";

                                      while (!(cin >> numeroCompte)) {
                                    cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
                                    cin.clear(); 
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
                                   }
                                   cout<<"\n\t\t\t\t |Recherche en cours...|";
                                   cout<<"\n";
                                    cout<<"[";
                                    	setColor(11);
	                                for( int i = 0;i<=50;i++){
		                           cout<<"#"<<flush;
		   
		                          this_thread::sleep_for(chrono::milliseconds(50));
		                            }
	                              cout<<"] Completed!"<<endl;
                                   setColor(7);
                            compte.afficherCompteSpecifique(numeroCompte);

							}else if(choix==5){
								cout<<"\n\t\t***************************************************";
								cout<<"\n\t\t\t\t >>   Affichage de tous les comptes   <<"<<endl;
								cout<<"\n\t\t***************************************************";
									cout<<"\n\n";
									
								compte.afficherTousLesComptes();
							}
							
						}while(choix!=6);
             break;
             
             case 3:
            	
            		cout<<"\n  Programme Quitter!"<<endl;
            		cout<<"\n\t Merci d'avoir utilise la gestion de banque.\n";
            		exit(0);
				
               break;
               default:
               	cout<<"\n\tchoix invalide entrer un nombre entre 1 a 3:"<<endl;
               	while (!(cin >> choix)) {
            cout << "Erreur de saisie!\n\n Veuillez entrer un chiffre : ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             
              }
               	//choix=controlsaisie();
               	continue;
        
                break;
            } 
			 
    }
    
       }while(choix!=6);

 }

	

 
 void  password_user()
 {
 	string pass_conect= "";
 	string nomprenom_conect="";
 	string  nomprenom= "";
 	string pass= "";
 	fstream file;
 	char ch;
 	int choix;
	 system("cls");
	do{
	
	 cout<<"\n\t\t\t---------------------------------------";
	 cout<<"\n\t\t\t|| BIENVENUE SUR NOTRE BANQUE   ||";
	 cout<<"\n\t\t\t----------------------------------------";
	 cout<<"\n\n\t\t\t Appuyer sur 1 pour Creer un compte";
	  cout<<"\n\n\t\t\t Appuyer sur 2 pour se Conntecter au compte";

	  cout<<"\n\n\t Veuillez entrer un choix:\t"<<endl;
	  cout<<"\n";
	  
			while (!(cin >> choix))	{
            cout << "Erreur de saisie!\n\n Veuillez utiliser des chiffres:\t "<<endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
             //menu();
            
             }
	   switch(choix)
	   {
	  
	   case 1:
	        if (choix==1){
			    cout<<" \n\t\t-------------------------------------------";
	    		cout<<"\n\t\t\t >> CREATION DE COMPTE <<"<<endl;
	    		cout<<"  \t\t-------------------------------------------";
	    		cout<<"\n\n\t\t\tEntrez votre Nom et Prenom:\t";
	    		cin.ignore();
	        	getline(cin,nomprenom_conect);
	        	
	    		cout<<"\n\tCreer un mot de passe:\t";
	    		 ch= getch();
	    		while(ch != 13)
	    		{
	    			pass_conect.push_back(ch);  
	    			cout<<"*";
	    			ch=getch();
				}
				file.open("Mops.txt",ios::app);  
	           file<<" "<< nomprenom_conect <<" "<< pass_conect <<"\n";
	            file.close();
	            cout<<"\n\t\t COMPTE ENREGISTRER AVEC SUCCES";
	             getch();
	              password_user();
	             
		}   
		break;
		
		 case 2:
		 if(choix==2)
		   {
		   	cout<<" \n\t\t-------------------------------------------";
	     	cout<<"\n\t\t\t >>  Connexion Employer  <<";
	    	cout<<" \n\t\t-------------------------------------------";
	    	
	   	    file.open("Mops.txt",ios::in );
	   	    
	   	       cout<<"\n\n\t\t\t Entrez votre Nom et Prenom:\t";
	    		cin.ignore();
	    	   getline(cin,nomprenom); //nom avec espace
	    	   
	    	   cout<<"\n\t Mot de passe:\t";
	    		
	    		ch= getch(); // ch compteur qui stocke le mot de passe qui sera masquee par la fonction getch
	    		
				while(ch != 13) //13 code ASSCI de la touche entree du clavier
	    		{
	    			pass.push_back(ch);  //recupere le mot entree par l'utilisateur stocker dans ch
	    			cout<<"*";
	    			ch=getch();
				}
				file>> nomprenom_conect >> pass_conect;
				
				while(!file.eof())
				{
					if ( pass==pass_conect && nomprenom==nomprenom_conect )
					{
							setColor(11);
						cout<<"\n\n\t\t\t\t| AUTHENTIFICATION |\n\t\t\t\t";
					
						cout<<"\n\t\t\t\t  CHARGEMENT"<<endl;
					
						for(int i=1; i<3; ++i)
						{
							cout<<"\t\t\t...";
							sleep(2);
						}
						cout<<"\r";
						cout<<"\n\n \t\t\t Connexion Reussie!\t";
							setColor(7);
						system("cls");
						 menu();
						cout.flush();
					break;
					}
				   else
				    {
				    		setColor(11);
					cout<<"\n\n\t\t\t\t| AUTHENTIFICATION |\n\t\t\t\t";
					
						cout<<"\n\t  CHARGEMENT"<<endl;
						for(int i=1; i<3; i++)
						{
							cout<<"\t\t...";
							sleep(2);
						}
						cout<<"\n\n\t\t ECHEC DE LA CONNEXION !";
						cout<<" \n\n\t\t MOT DE PASSE OU NOM INVALIDE\t";
							setColor(7);
						cout.flush();
						cout<<"\n";
						password_user();
						break;
				   }
					file >> nomprenom_conect >> pass_conect;
				}
				file.close();
					
	   	}
	   	break;
		   
		   default:
		   		cout<<"Invalide! ressayer entre 1 et 2:\t";
	   		 
             continue;
	   		//password_user();
		   break;
	   	 }
	}while( choix!=2);

	
 }
 
 bool isAlpha(const std::string& str)
 {
 	for(char c: str)
 	{
 		if (!std::isalpha(c))
 		{
 			return false;
		 }
	 }
	 return true;
 }
 
 //function to display a welcome animation
void displayWelcomeMessage()
{
	string message="\n\n\t\t\t\t Welcome to BFAST international BANK \n\n\t\t This Program has been elaborated by :\n\n\t\t AMADOU SEKOU HALIDOU \n\n\t\t SOUMANA ISSA FATOUMATA \n\n\t\t ELH ADAMOU OUSMANE \n\n\t\t\t BOUBACAR MOUSSA GARBA SAMIRA\n\n\t\t\t ANASS ABDOUL-SALAM";
	setColor(11);
	for(char c: message){
		cout<< c << flush;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	setColor(7);//default color
	cout<<endl;
}

//function to display a colorful menu
void showColorfulMenu(){
	string options[]={
		"BINVENUE!\n Wa FONDA KAYAAN! ",
		"\n\tBFAST \t:\t BANQUE RAPIDE ",
		"\n\t AGENCE n_202 TCHANGAREY\t\t\t NOTRE SLOGAN\t: RAYONNER VOTRE MANIERE DE VIVRE ",
		"\n\tBP_NY/NIGER\t:\t 2154"
	};
	for(int i = 0;i<4;i++){
		setColor(i + 9);//change color for each option
		cout<<options[i]<<endl;
		this_thread::sleep_for(chrono::milliseconds(300));
	}
	setColor(7);//reset to default color
}


int main()
 {
 	    sleep(3);
 	    cout<<"\n\n\t";
 	  showColorfulMenu();
 	    cout<<"\n\n\t";
      displayWelcomeMessage();
       cout<<"\n\n";
       system("pause");
	password_user();
	 // menu();


    return 0;

}


