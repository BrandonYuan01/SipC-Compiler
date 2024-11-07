#include "TipArray.h"
#include "TipTypeVisitor.h"

TipArray::TipArray(std::vector<std::shared_ptr<TipType>> inits)
    : TipCons(inits) {arr_of = false;}

TipArray::TipArray(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2)
    : TipCons(combine(expr1, expr2)) {arr_of = true;}

std::vector<std::shared_ptr<TipType>>
TipArray::combine(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2) {
                    std::vector<std::shared_ptr<TipType>> combined;
    combined.push_back(std::move(expr1));
    combined.push_back(std::move(expr2));
    return combined;
}

bool TipArray::operator==(const TipType &other) const {
    // All elements in the comparing arrays should be the same type e.g. [1, 1, 1] == [1, 1, 1, 1, 1]
    auto otherTipArray = dynamic_cast<const TipArray *>(&other);
    if (!otherTipArray) {
        return false;
        }
    
    if (arity() != otherTipArray->arity()) {
        return false;
        }
    
    if (arr_of && otherTipArray->arr_of){
        if (*(arguments.at(1)) != *(otherTipArray->arguments.at(1))) {
            return false;
        }
    }

    if (arr_of){
        if (*(arguments.at(1)) != *(otherTipArray->arguments.at(0))){
            return false;
        }
    }

    if (otherTipArray->arr_of){
        if (*(arguments.at(0)) != *(otherTipArray->arguments.at(1))){
            return false;
            }
        }


    for (int i = 0; i < arity(); i++) {
        if (*(arguments.at(i)) != *(otherTipArray->arguments.at(i))) {
            return false;
        }
    }

    
    return true;
    }

bool TipArray::operator!=(const TipType &other) const {
  return !(*this == other);
}


std::ostream &TipArray::print(std::ostream &out) const {
if (arr_of){
    out << "[";

}
    out << "[";
    bool first = true;
    int i = 0;
    for (auto &init : arguments) {
    if (first) {
        out << *init;
        first = false;
        continue;
    }
    out << "," << *init;
    }
    out << "]";
    return out;
    }

std::vector<std::shared_ptr<TipType>> &TipArray::getInits() {
  return arguments;
}


void TipArray::accept(TipTypeVisitor *visitor) {
  if (visitor->visit(this)) {
    for (auto a : arguments) {
      a->accept(visitor);
    }
  }
  visitor->endVisit(this);
}
