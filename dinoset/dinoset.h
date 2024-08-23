#pragma once
#include <iostream>
#include <string>

const int total_dinos = 8;



enum class DinoId {
    velociraptor,        // 0
    stegosaurus,         // 1
    tyrannosaurus,       // 2
    procompsognathus,    // 3
    triceratops,         // 4
    pachycephalosaurus,  // 5
    parasaurolophus,     // 6
    pteranodon           // 7
};

class DinoSet{
  public:
  void add(DinoId id)
    {
        int index = static_cast<int>(id);
        _dino[index] = true;
    }

  void remove(DinoId id)
    {
        int index = static_cast<int>(id);
        _dino[index] = false;
    }

  bool contains(DinoId id) const
    {
        int index = static_cast<int>(id);
        return _dino[index];
    }

  int size() const{
      int counter=0;
      for (int i=0;i<total_dinos;i++){
        if (_dino[i]){
          counter+=1;
        }
      }
      
      return counter;
    }


  bool is_empty() const{
      if(this->size()==0){
        return true;
      }
      else{
        return false;
      }
    }

    //union of sets
    DinoSet operator+(const DinoSet& other) const
    {
        DinoSet result;
        for (int i = 0; i < total_dinos; i++) {
            DinoId id = static_cast<DinoId>(i);
            if (this->contains(id) or other.contains(id)) {
                result.add(id);
            }
        }
        return result;
    }

    DinoSet operator*(const DinoSet& other) const
    {
        DinoSet result;
        for (int i = 0; i < total_dinos; i++) {
            DinoId id = static_cast<DinoId>(i);
            if (this->contains(id) and other.contains(id)) {
                result.add(id);
            }
        }
        return result;
    }

    DinoSet operator-(const DinoSet& other) const
    {
        DinoSet result;
        for (int i = 0; i < total_dinos; i++) {
            DinoId id = static_cast<DinoId>(i);
            if (this->contains(id) and (other.contains(id)==false)) {
                result.add(id);
            }
        }
        return result;
    }

    DinoSet operator!() const
    {
        DinoSet result;
        for (int i = 0; i < total_dinos; i++) {
            if (this->contains(static_cast<DinoId>(i)) == 0) {
                result.add(static_cast<DinoId>(i));
            }
        }
        return result;
    }

    bool operator==(const DinoSet& other) const
    {
        int mismatch = 0;
        for (int i = 0; i < total_dinos; i++) {
            if (this->contains(static_cast<DinoId>(i)) != other.contains(static_cast<DinoId>(i))) {
                mismatch+=1;
            }
        }
        if (mismatch == 0) {
            return true;
        } else {
            return false;
        }
    }

    std::string to_string() const
    {
        std::string result = "{";
        for (int i = 0; i < total_dinos; i++) {
          if (_dino[i]){
            result=result+_names[i]+", ";
          }
        }
        if(this->is_empty()){
          result=result+"}";
          }
        else{
          result.erase(result.size()-2,result.size()-1);
          result=result+"}";
        }
        
        
        return result;
    }


  private:
    bool _dino[total_dinos]{};
    std:: string _names[total_dinos]{"velociraptor","stegosaurus",         // 1
    "tyrannosaurus","procompsognathus","triceratops",
    "pachycephalosaurus","parasaurolophus","pteranodon"};
      };



