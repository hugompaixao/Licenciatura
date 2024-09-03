package SymbolTable;

import org.antlr.v4.runtime.Token;

import java.util.ArrayList;

public class TypeSymbol extends Symbol{

    ArrayList<Symbol> atributos = new ArrayList<Symbol>();

    String typeName;

    public TypeSymbol(Token token, Type retType) {
        super(token, retType);
    }

    public ArrayList<Symbol> get_atributos() {return atributos;}
    public void add_atributos( Symbol sym ) { atributos.add(sym); }

    public Symbol get_atributo(String name){
        for (Symbol s : get_atributos()){
            if(s.getToken().getText().compareTo(name) == 0) return s;
        }
        return null;
    }

    //public String toString() { return "type"+super.toString()+"["+atributos+"]"+"{"+typeName+"}"; }
    public String toString() { return typeName; }

    public void setName(String name) {typeName = name;}
    public String getName() {return typeName;}
}