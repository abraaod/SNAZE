/**
 * @file snake.h
 * @brief Arquivo com o cabeçalho da classe Snake.
 * @author $Autor: Abraão Vitor Lopes Dantas $
 * @author $Autor: Daniel Henrique Ferreira Gomes $
 * \version $Versão: 1.0 $
 * \date $Data: 2018// :: $
 * Contact: abraaovld@gmail.com & danielhenriquefg@gmail.com
 *
*/

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <iostream>
#include <deque>

struct Pos{
    size_t linha;
    size_t coluna;

    Pos(size_t l = 0, size_t c = 0) : linha (l), coluna (c){};
    bool operator== ( const Pos & rhs )
    {
        return linha == rhs.linha and coluna == rhs.coluna;
    }
    bool operator!= ( const Pos & rhs )
    {
        return linha != rhs.linha or coluna != rhs.coluna;
    }
    Pos & operator= ( const Pos & rhs )
    {
        linha = rhs.linha;
        coluna = rhs.coluna;
        return *(this);
    }
    friend std::ostream & operator<<( std::ostream& os_, const Pos & p_ ){
          os_ << p_.linha << " " << p_.coluna;
          return os_;
        }
};

struct State{
    enum code_t {
      ALIVE = 0,
      CRASH,
      DEAD,
      WIN
    };
    code_t status;
    explicit State( code_t type_=ALIVE) : status{ type_ } {/* Empty */}
    friend std::ostream & operator<<( std::ostream& os_, const State & s_ ){
          os_ << s_.status;
          return os_;
        }
};

class Snake
{
    public:
      Snake(Pos p) : head("\u25C8"), score(0), lives(5), state(State::ALIVE) {
        snk.push_back(p);
      };
      Snake() : snk(0), head("\u25C8"), score(0), lives(5), state(State::ALIVE) { };
      virtual ~Snake(){};
      Snake & operator= ( Snake & rhs )
      {
          snk = rhs.get_snk();
          head = rhs.get_head();
          score = rhs.get_score();
          lives = rhs.get_lives();
          state = rhs.get_state();
          return *(this);
      }

      /*Snake operator =(const Snake & s){
        Snake snk;
        snk.snk = s.snk;
        snk.head = s.head;
        snk.score = s.score;
        snk.state = s.state;

        return snk;
      }*/
        size_t size () const{
          return snk.size();
        }
        Pos get_pos_head ( void ){
          return snk.front();
        }
        std::deque < Pos > get_snk( ) const{
          return snk;
        }

        void set_simb_cab ( std::string cab ){
          head = cab;
        }

        //Verifica se para a cobra ocupa uma determinada posição
        bool ocupado_snk( const Pos & pos ){
          auto begin = snk.begin();
          auto end = snk.end();
          while(begin != end){
            if(*begin == pos){
              return true;
            }
            begin++;
          }
          return false;
        }

        void mover( Pos pos ){
          snk.push_front(pos);
          snk.pop_back();
        }
        void comer( Pos pos ){
          snk.push_front(pos);
          score += 100;
        }

        void clear(){
          snk.clear();
          lives = 5;
        }

        void print ()
        {

            auto begin = snk.begin();
            auto end = snk.end();
            while(begin != end){
                std::cout << begin->linha << begin->coluna << ".";
                begin++;
            }
        }
        std::string get_head()
        {
            return head;
        }
        int get_score()
        {
            return score;
        }
        int get_lives()
        {
            return lives;
        }
        void set_lives(int l)
        {
            lives = l;
        }
        State get_state()
        {
            return state;
        }
        void kill()
        {
          snk.clear();
          --lives;
          state.status = State::code_t::DEAD;
        }
        void live(Pos pos)
        {
          state.status = State::code_t::ALIVE;
          snk.push_front(pos);
        }

        void win(){
          state.status = State::code_t::WIN;
        }

        void dead(){
          state.status = State::code_t::DEAD;
        }

    private:
        std::deque<Pos>snk;         //!< Corpo completo da cobra
        std::string head;           //!< Simbolo que representa a cabeça da cobra
        int score;
        int lives;                  //!< Número de Vidas da cobra
        State state;                //Estado atual da cobra
};

#endif
