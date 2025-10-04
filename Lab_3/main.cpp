#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Convierte un caracter en 8 bits (como string)
string charToBits(unsigned char c) {
    string bits="";
    for(int i=7;i>=0;i--){
        bits += ((c>>i)&1) ? '1':'0';
    }
    return bits;
}

// Convierte 8 bits ('0'/'1') en caracter
unsigned char bitsToChar(const string &bits) {
    unsigned char c=0;
    for(int i=0;i<8;i++){
        c = (c<<1) | (bits[i]-'0');
    }
    return c;
}

// Para arreglos de enteros (versión char[])
void charToBitsArr(unsigned char c, int bits[8]){
    for(int i=7;i>=0;i--){
        bits[7-i] = (c>>i)&1;
    }
}
unsigned char bitsToCharArr(int bits[8]){
    unsigned char c=0;
    for(int i=0;i<8;i++){
        c = (c<<1) | bits[i];
    }
    return c;
}

// Invertir todos
template<typename T>
void invertirTodos(T &bloque){
    for(auto &b: bloque){
        b = (b=='0'?'1':'0');
    }
}
void invertirTodosArr(int bloque[],int n){
    for(int i=0;i<n;i++) bloque[i]=1-bloque[i];
}

// Invertir cada 2
template<typename T>
void invertirCada2(T &bloque){
    for(size_t i=0;i+1<bloque.size();i+=2){
        bloque[i]   = (bloque[i]=='0'?'1':'0');
        bloque[i+1] = (bloque[i+1]=='0'?'1':'0');
    }
}
void invertirCada2Arr(int bloque[],int n){
    for(int i=0;i+1<n;i+=2){
        bloque[i]=1-bloque[i];
        bloque[i+1]=1-bloque[i+1];
    }
}

// Invertir cada 3
template<typename T>
void invertirCada3(T &bloque){
    for(size_t i=0;i+2<bloque.size();i+=3){
        for(int k=0;k<3;k++)
            bloque[i+k]=(bloque[i+k]=='0'?'1':'0');
    }
}
void invertirCada3Arr(int bloque[],int n){
    for(int i=0;i+2<n;i+=3){
        for(int k=0;k<3;k++) bloque[i+k]=1-bloque[i+k];
    }
}

// Rotar derecha
void rotarDerechaStr(string &bloque){
    if(bloque.size()<=1) return;
    char last=bloque.back();
    for(int i=bloque.size()-1;i>0;i--) bloque[i]=bloque[i-1];
    bloque[0]=last;
}
void rotarDerechaArr(int bloque[],int n){
    if(n<=1) return;
    int ultimo=bloque[n-1];
    for(int i=n-1;i>0;i--) bloque[i]=bloque[i-1];
    bloque[0]=ultimo;
}

// Rotar izquierda
void rotarIzquierdaStr(string &bloque){
    if(bloque.size()<=1) return;
    char first=bloque[0];
    for(size_t i=0;i<bloque.size()-1;i++) bloque[i]=bloque[i+1];
    bloque.back()=first;
}
void rotarIzquierdaArr(int bloque[],int n){
    if(n<=1) return;
    int primero=bloque[0];
    for(int i=0;i<n-1;i++) bloque[i]=bloque[i+1];
    bloque[n-1]=primero;
}

// ============================================================================
// VERSION CON STRING
// ============================================================================
void codificarMetodo1Str(ifstream &in, ofstream &out, int n){
    string bloque="", prev="";
    bool primer=true;
    int b;
    while((b=in.get())!=EOF){
        bloque+=charToBits((unsigned char)b);
        while((int)bloque.size()>=n){
            string actual=bloque.substr(0,n);
            bloque.erase(0,n);
            if(primer){
                invertirTodos(actual);
                primer=false;
            } else {
                int unos=0,ceros=0;
                for(char c:prev){ if(c=='1') unos++; else ceros++; }
                if(unos==ceros) invertirTodos(actual);
                else if(ceros>unos) invertirCada2(actual);
                else invertirCada3(actual);
            }
            prev=actual;
            for(size_t i=0;i<actual.size();i+=8){
                string temp=actual.substr(i,8);
                while(temp.size()<8) temp+='0';
                out.put(bitsToChar(temp));
            }
        }
    }
    if(!bloque.empty()){
        string actual=bloque;
        if(primer) invertirTodos(actual);
        else {
            int unos=0,ceros=0;
            for(char c:prev){ if(c=='1') unos++; else ceros++; }
            if(unos==ceros) invertirTodos(actual);
            else if(ceros>unos) invertirCada2(actual);
            else invertirCada3(actual);
        }
        for(size_t i=0;i<actual.size();i+=8){
            string temp=actual.substr(i,8);
            while(temp.size()<8) temp+='0';
            out.put(bitsToChar(temp));
        }
    }
}
void decodificarMetodo1Str(ifstream &in, ofstream &out, int n){
    string bloque="", prev="";
    bool primer=true;
    int b;
    while((b=in.get())!=EOF){
        bloque+=charToBits((unsigned char)b);
        while((int)bloque.size()>=n){
            string actual=bloque.substr(0,n);
            bloque.erase(0,n);
            if(primer){ invertirTodos(actual); primer=false; }
            else {
                int unos=0,ceros=0;
                for(char c:prev){ if(c=='1') unos++; else ceros++; }
                if(unos==ceros) invertirTodos(actual);
                else if(ceros>unos) invertirCada2(actual);
                else invertirCada3(actual);
            }
            prev=actual;
            for(size_t i=0;i<actual.size();i+=8){
                string temp=actual.substr(i,8);
                while(temp.size()<8) temp+='0';
                out.put(bitsToChar(temp));
            }
        }
    }
}
void codificarMetodo2Str(ifstream &in, ofstream &out,int n){
    string bloque=""; int b;
    while((b=in.get())!=EOF){
        bloque+=charToBits((unsigned char)b);
        while((int)bloque.size()>=n){
            string actual=bloque.substr(0,n);
            bloque.erase(0,n);
            rotarDerechaStr(actual);
            for(size_t i=0;i<actual.size();i+=8){
                string temp=actual.substr(i,8);
                while(temp.size()<8) temp+='0';
                out.put(bitsToChar(temp));
            }
        }
    }
}
void decodificarMetodo2Str(ifstream &in, ofstream &out,int n){
    string bloque=""; int b;
    while((b=in.get())!=EOF){
        bloque+=charToBits((unsigned char)b);
        while((int)bloque.size()>=n){
            string actual=bloque.substr(0,n);
            bloque.erase(0,n);
            rotarIzquierdaStr(actual);
            for(size_t i=0;i<actual.size();i+=8){
                string temp=actual.substr(i,8);
                while(temp.size()<8) temp+='0';
                out.put(bitsToChar(temp));
            }
        }
    }
}

// ============================================================================
// VERSION CON ARREGLOS char[]
// ============================================================================
void codificarMetodo1Arr(ifstream &in, ofstream &out,int n){
    int bits[1024], prev[1024], tamBloque=0; bool primer=true; int b;
    while((b=in.get())!=EOF){
        int charBits[8]; charToBitsArr((unsigned char)b,charBits);
        for(int i=0;i<8;i++){
            bits[tamBloque++]=charBits[i];
            if(tamBloque==n){
                if(primer){ invertirTodosArr(bits,n); primer=false;}
                else {
                    int unos=0,ceros=0;
                    for(int j=0;j<n;j++) if(prev[j]) unos++; else ceros++;
                    if(unos==ceros) invertirTodosArr(bits,n);
                    else if(ceros>unos) invertirCada2Arr(bits,n);
                    else invertirCada3Arr(bits,n);
                }
                for(int j=0;j<n;j+=8){
                    int temp[8];
                    for(int k=0;k<8;k++) temp[k]=(j+k<n?bits[j+k]:0);
                    out.put(bitsToCharArr(temp));
                }
                for(int j=0;j<n;j++) prev[j]=bits[j];
                tamBloque=0;
            }
        }
    }
}
void decodificarMetodo1Arr(ifstream &in, ofstream &out,int n){
    int bits[1024], prev[1024], tamBloque=0; bool primer=true; int b;
    while((b=in.get())!=EOF){
        int charBits[8]; charToBitsArr((unsigned char)b,charBits);
        for(int i=0;i<8;i++){
            bits[tamBloque++]=charBits[i];
            if(tamBloque==n){
                if(primer){ invertirTodosArr(bits,n); primer=false;}
                else {
                    int unos=0,ceros=0;
                    for(int j=0;j<n;j++) if(prev[j]) unos++; else ceros++;
                    if(unos==ceros) invertirTodosArr(bits,n);
                    else if(ceros>unos) invertirCada2Arr(bits,n);
                    else invertirCada3Arr(bits,n);
                }
                for(int j=0;j<n;j+=8){
                    int temp[8];
                    for(int k=0;k<8;k++) temp[k]=(j+k<n?bits[j+k]:0);
                    out.put(bitsToCharArr(temp));
                }
                for(int j=0;j<n;j++) prev[j]=bits[j];
                tamBloque=0;
            }
        }
    }
}
void codificarMetodo2Arr(ifstream &in, ofstream &out,int n){
    int bits[1024], tamBloque=0, b;
    while((b=in.get())!=EOF){
        int charBits[8]; charToBitsArr((unsigned char)b,charBits);
        for(int i=0;i<8;i++){
            bits[tamBloque++]=charBits[i];
            if(tamBloque==n){
                rotarDerechaArr(bits,n);
                for(int j=0;j<n;j+=8){
                    int temp[8];
                    for(int k=0;k<8;k++) temp[k]=(j+k<n?bits[j+k]:0);
                    out.put(bitsToCharArr(temp));
                }
                tamBloque=0;
            }
        }
    }
}
void decodificarMetodo2Arr(ifstream &in, ofstream &out,int n){
    int bits[1024], tamBloque=0, b;
    while((b=in.get())!=EOF){
        int charBits[8]; charToBitsArr((unsigned char)b,charBits);
        for(int i=0;i<8;i++){
            bits[tamBloque++]=charBits[i];
            if(tamBloque==n){
                rotarIzquierdaArr(bits,n);
                for(int j=0;j<n;j+=8){
                    int temp[8];
                    for(int k=0;k<8;k++) temp[k]=(j+k<n?bits[j+k]:0);
                    out.put(bitsToCharArr(temp));
                }
                tamBloque=0;
            }
        }
    }
}

int main(){
    cout<<"Elija version:\n1. Usando arreglos char[]\n2. Usando string\nOpcion: ";
    int version; cin>>version;
    cout<<"Menu:\n1. Codificar\n2. Decodificar\n3. Salir\nOpcion: ";
    int opcion; cin>>opcion;
    if(opcion==3) return 0;

    string inFile,outFile;
    cout<<"Archivo de entrada: "; cin>>inFile;
    cout<<"Archivo de salida: "; cin>>outFile;
    int n, metodo;
    cout<<"Valor de n (tamano bloque): "; cin>>n;
    cout<<"Metodo (1 o 2): "; cin>>metodo;

    ifstream in(inFile, ios::binary);
    ofstream out(outFile, ios::binary);
    if(!in||!out){ cout<<"Error con archivos\n"; return 1;}

    if(version==1){ // char[]
        if(opcion==1){
            if(metodo==1) codificarMetodo1Arr(in,out,n);
            else codificarMetodo2Arr(in,out,n);
        } else {
            if(metodo==1) decodificarMetodo1Arr(in,out,n);
            else decodificarMetodo2Arr(in,out,n);
        }
    } else { // string
        if(opcion==1){
            if(metodo==1) codificarMetodo1Str(in,out,n);
            else codificarMetodo2Str(in,out,n);
        } else {
            if(metodo==1) decodificarMetodo1Str(in,out,n);
            else decodificarMetodo2Str(in,out,n);
        }
    }

    in.close(); out.close();
    cout<<"Proceso terminado.\n";
    return 0;
}
