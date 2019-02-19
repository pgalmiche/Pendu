#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm> // pour transform

#include "randomnumber.hpp"
#define LIFE 10

/**
 * Jeu du pendu pour terminal
 *
 * Authors : Léo Bois, Pierre Galmiche, Mickael Bestard, Valentin Ritz.
 *
 */


// -------------------- STRUCT --------------------
/* Pertinence de séparer STRUCT et CLASS : on en discutera */

struct str_toupper // mettre en majucule un mot d'un coup
{
    char operator()(char c) const
    {
        return std::toupper(static_cast<unsigned char>(c));
    }
};


// -------------------- FUNCTIONS --------------------

std::string random_word(){
    std::vector<std::string> dico;
    dico = {"MOT", "TEST", "COUCOU", "ENJOY"}; // à remplir depuis un fichier
    RandomNumber<int> rnd(0,dico.size());
    return dico[rnd()];
}

char get_letter()
{
    char letter;
    bool correct = false;

    while (!correct)
    {
        std::cout << " > ";
        std::cin >> letter;

        if (!(isalpha(letter))){
            std::cout << "Not a letter, try again." << std::endl;
        } else {
            correct = true;
        }
    }
    return toupper(letter);
}//Retourne la lettre entrée en majuscule

std::string get_sword(){

    std::string word;

    bool correct = false;
    while (!correct){

        correct = true;

        std::cout << "Player 1: entrez un mot secret" << std::endl;
        std::cout << " > ";
        std::cin >> word;

        for (int i = 0; i < word.size(); ++i) {
            if (!(isalpha(word[i]))){ // Code à factoriser ? (cf get_letter)
                std::cout << "Not a word, try again." << std::endl;
                correct = false;
                break;
            }
        }
    }
    std::transform(word.begin(), word.end(), word.begin(), str_toupper());

    return word;
}


// -------------------- CLASS --------------------

class Game
{

	public:

		Game(bool random = true, std::string word = "DEFAULT") {

            if (random) {
                sword = random_word();
            } else {
                sword = word;// Donné par player 1. (Mettre en majuscules)
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
            std::cout << "Nombre de vies restantes : " << LIFE - nmistakes <<
            "\nlettre à trouver : ";
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
                if(l == sword[i] && !found[i]){
                    isIn = true;
                    found[i] = true;
                    break;
                }
            }
            if(!isIn){
                nmistakes++;
                if(nmistakes == 10){
                    is_over = true;
                }
            }
            if(std::accumulate(found.begin(), found.end(), 0) == sizeW){
                is_over = true;
            }
		}


		void print_result() const{
            std::cout << "Nombre d'erreurs : " << nmistakes << std::endl;
            if(nmistakes == LIFE){
                std::cout << "Vous avez perdu ... Try again!" << std::endl;
            }
            else{
                std::cout << "Vous avez gagné ... BRAVO!" << std::endl;
            }
		}


		std::string get_secret() { //fonction inutile (pour tester)
		    return sword;
		}


	private:

        friend std::string random_word();
		std::string	        sword;// Par exemple SECRET (S E C R E T)
		std::vector<bool>	found;// Par exemple FFTFFT (_ _ C _ _ T)
		int                 sizeW;// Stocke la taille du mot secret
		int     nmistakes;
		bool    is_over;
};//Fin classe Game


// -------------------- MAIN --------------------

int main()
{
    std::string word;

    word = get_sword();

	Game game(false,word);
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
