#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctype.h>

#include "randomnumber.hpp"

#define LIFE 10

/**
 * Jeu du pendu pour terminal
 *
 * Authors : Léo Bois, Pierre Galmiche, Mickael Bestard, Valentin Ritz.
 *
 */

class Game
{

	public:

		Game(bool random = true, std::string word = "DEFAULT") {

            if (random) {
                dico = {"MOT", "TEST", "COUCOU", "ENJOY"}; // remplir depuis fichier
                sword = random_word();
            } else {
                sword = word;// Donné par player 1. Mettre en majuscules
            }

            sizeW = sword.size();
            nmistakes = 0;
            is_over = 0;

            for(int i=0; i<sizeW; i++){
                found.push_back(0);
            }
		}


		bool over() const {
            return is_over;
        }


		void print_state() const{
            std::cout << "Nombre de vies restantes : " << LIFE - nmistakes << "\nlettre à trouver : ";
            for(int i=0; i<sizeW; i++){
                if(found[i] == 1){
                    std::cout << sword[i] << " ";
                }
                else{
                    std::cout << "_ ";
                }
            }
            std::cout << "\n\n";
		}


		void submit(const char l){
            bool isIn = 0;
            for(int i=0; i<sizeW; i++){
                if(l == sword[i] && found[i] == 0){
                    isIn = 1;
                    found[i] = 1;
                    break;
                }
            }
            if(!isIn){
                nmistakes++;
                if(nmistakes == 10){
                    is_over = 1;
                }
            }
            if(std::accumulate(found.begin(), found.end(), 0) == sizeW){
                is_over = 1;
            }
		}


		void print_result() const{
            std::cout << "Nombre d'erreurs : " << nmistakes << "\n";
            if(nmistakes == LIFE){
                std::cout << "Vous avez perdu ... Try again!\n";
            }
            else{
                std::cout << "Vous avez gagné ... BRAVO!\n";
            }
		}


		std::string get_secret() {
		    return sword;
		}


	private:

		std::string random_word(){
		    RandomNumber<int> rnd(0,3);
		    return dico[rnd()];
		}

		std::string	        sword;// Par exemple SECRET (S E C R E T)
		std::vector<bool>	found;// Par exemple FFTFFT (_ _ C _ _ T)
		int                 sizeW;// Stocke la taille du mot secret

		std::vector<std::string> dico;

		int     nmistakes;
		bool    is_over;
};//Fin classe Game


char get_letter()// Pierre
{
    char letter;
    bool correct = false;

    while (!correct)
    {
        std::cout << " > ";
        std::cin >> letter;

        if (!(isalpha(letter))){
            std::cout << "Not a letter, try again." << std::endl;
        } else{
            correct = true;
        }
    }
    return toupper(letter);
}//Retourne la lettre entrée en majuscule


int main()
{
	Game game(true);
	std::cout << "sword : " << game.get_secret() << std::endl;
    game.print_state();
	while(!game.over())
	{
		// Demande au joueur de saisir une lettre (et une seule)
		char a;
		a = get_letter();
		// Met à jour les attributs de game
		game.submit(a);
		game.print_state();
	}
	game.print_result();
	return 0;
}
