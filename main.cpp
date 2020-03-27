#include <iostream>
#include <stdexcept>

class Move {
  public:
    Move(int sh, int sc, int th, int tc): source(sh), source_coins(sc), target(th), target_coins(tc) {}

    int getSource() const {
      return source;
    }
    int getSourceCoins() const {
      return source_coins;
    }
    int getTarget() const {
      return target;
    }
    int getTargetCoins() const {
      return target_coins;
    }

    friend std::ostream & operator << (std::ostream &out, const Move &move){
      out<<"takes "<<move.source_coins<<" coins from heap "<<move.source<<" and puts ";
      if (move.target_coins>0) out<<move.target_coins<<" coins to heap "<<move.target;
      else out<<"nothing";
      return out;
    }

  private:
      int source, source_coins, target, target_coins;
};

class State {
  public:
    State (int  h, const int c[]): heaps(h), h_coins(new int[h]) {
      for (int i=0; i<h; i++) h_coins[i]=c[i];
    }
    ~State() {
      delete [] h_coins;
    }

    void next(const Move &move) throw(std::logic_error){
      if (move.getSource()<0 || move.getSource()>=heaps || 
          move.getTarget()<0 || move.getTarget()>=heaps ||
          move.getSourceCoins()<=0 || move.getTargetCoins()<0 ||
          move.getSourceCoins()>h_coins[move.getSource()] || move.getTargetCoins()>=move.getSourceCoins())
        throw std::logic_error("invalid move");
      h_coins[move.getSource()]-=move.getSourceCoins();
      if (move.getTargetCoins()>0) h_coins[move.getTarget()]+=move.getTargetCoins();
      State(heaps,h_coins);
    }
    bool winning() const {
      int i=0;
      while (h_coins[i++]==0);
      return i>heaps;
    }

    int getHeaps() const {
      return heaps;
    }
    int getCoins(int h) const throw(std::logic_error){
      if (h<0 || h>=heaps) throw std::logic_error("invalid heap");
      return h_coins[h];
    }

    friend std::ostream & operator << (std::ostream &out, const State &state){
      for (int i=0; i<state.heaps-1; i++) out<<state.h_coins[i]<<", ";
      out<<state.h_coins[state.heaps-1];
      return out;
    }

  private:
    int heaps;
    int *h_coins;
};
