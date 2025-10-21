#include <iostream> 

template <typename T>
class MatrizBase {
protected:
    int _filas;
    int _columnas;

public:
    MatrizBase(int f, int c) {
        _filas = f;
        _columnas = c;
    }

    virtual ~MatrizBase() {
    }


    virtual void cargarValores() = 0;

    virtual void imprimir() const = 0;

    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otra) const = 0;
    
    virtual T get(int f, int c) const = 0;
    
    virtual void set(int f, int c, T val) = 0;

    int getFilas() const { return _filas; }
    int getColumnas() const { return _columnas; }
};


template <typename T>
class MatrizDinamica : public MatrizBase<T> {
private:
    T **_datos; 

public:
    MatrizDinamica(int f, int c) : MatrizBase<T>(f, c) {
        std::cout << "Creando Matriz Dinámica (" << f << "x" << c << ")..." << std::endl;
        
        _datos = new T*[this->_filas];
        
        for (int i = 0; i < this->_filas; i++) {
            _datos[i] = new T[this->_columnas];
        }
    }


    virtual ~MatrizDinamica() {
        std::cout << "Llamando al destructor de Matriz Dinámica..." << std::endl;
        
        for (int i = 0; i < this->_filas; i++) {
            delete[] _datos[i]; 
        }
        
        delete[] _datos;
        std::cout << "Liberando memoria de Matriz Dinámica..." << std::endl;
    }

    MatrizDinamica(const MatrizDinamica<T>& otra) : MatrizBase<T>(otra._filas, otra._columnas) {
        std::cout << "(Copia profunda) Creando copia de Matriz Dinámica..." << std::endl;
        
        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; i++) {
            _datos[i] = new T[this->_columnas];
        }

        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                this->_datos[i][j] = otra._datos[i][j];
            }
        }
    }

    MatrizDinamica<T>& operator=(const MatrizDinamica<T>& otra) {
        std::cout << "(Copia profunda) Asignando Matriz Dinámica..." << std::endl;

        if (this == &otra) {
            return *this;
        }

        for (int i = 0; i < this->_filas; i++) {
            delete[] _datos[i];
        }
        delete[] _datos;

        this->_filas = otra._filas;
        this->_columnas = otra._columnas;

        _datos = new T*[this->_filas];
        for (int i = 0; i < this->_filas; i++) {
            _datos[i] = new T[this->_columnas];
        }

        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                this->_datos[i][j] = otra._datos[i][j];
            }
        }

        return *this; 
    }


    virtual T get(int f, int c) const {
        return _datos[f][c];
    }
    
    virtual void set(int f, int c, T val) {
        _datos[f][c] = val;
    }

    virtual void cargarValores() {
        if (this->_filas == 3 && this->_columnas == 2) {
            set(0, 0, (T)1.5); set(0, 1, (T)2.0);
            set(1, 0, (T)0.0); set(1, 1, (T)1.0);
            set(2, 0, (T)4.5); set(2, 1, (T)3.0);
        }
         if (this->_filas == 2 && this->_columnas == 2) {
            set(0, 0, (T)10); set(0, 1, (T)20);
            set(1, 0, (T)30); set(1, 1, (T)40);
        }
    }

    virtual void imprimir() const {
        std::cout << "Imprimiendo Matriz Dinámica (" << this->_filas << "x" << this->_columnas << "):" << std::endl;
        for (int i = 0; i < this->_filas; i++) {
            std::cout << "| ";
            for (int j = 0; j < this->_columnas; j++) {
                std::cout << _datos[i][j] << " | ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otra) const {
        std::cout << "(Suma manejada por MatrizDinamica)" << std::endl;
        
        if (this->_filas != otra.getFilas() || this->_columnas != otra.getColumnas()) {
            std::cout << "Error: No se pueden sumar matrices de diferentes dimensiones." << std::endl;
            return nullptr; 
        }

        MatrizDinamica<T>* resultado = new MatrizDinamica<T>(this->_filas, this->_columnas);

        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                T val1 = this->get(i, j); 
                T val2 = otra.get(i, j);
                resultado->set(i, j, val1 + val2);
            }
        }

        return resultado;
    }
};


template <typename T, int M, int N>
class MatrizEstatica : public MatrizBase<T> {
private:
    T _datos[M][N]; 

public:
    MatrizEstatica() : MatrizBase<T>(M, N) {
        std::cout << "Creando Matriz Estática (" << M << "x" << N << ")..." << std::endl;
    }

    virtual ~MatrizEstatica() {
        std::cout << "Destruyendo Matriz Estática (automático)..." << std::endl;
    }


    virtual T get(int f, int c) const {
        return _datos[f][c];
    }
    
    virtual void set(int f, int c, T val) {
        _datos[f][c] = val;
    }

    virtual void cargarValores() {
        if (M == 3 && N == 2) {
            set(0, 0, (T)0.5); set(0, 1, (T)1.0);
            set(1, 0, (T)2.0); set(1, 1, (T)3.0);
            set(2, 0, (T)1.0); set(2, 1, (T)1.0);
        }
         if (M == 2 && N == 2) {
            set(0, 0, (T)1); set(0, 1, (T)2);
            set(1, 0, (T)3); set(1, 1, (T)4);
        }
    }

    virtual void imprimir() const {
        std::cout << "Imprimiendo Matriz Estática (" << this->_filas << "x" << this->_columnas << "):" << std::endl;
        for (int i = 0; i < this->_filas; i++) {
            std::cout << "| ";
            for (int j = 0; j < this->_columnas; j++) {
                std::cout << _datos[i][j] << " | ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    virtual MatrizBase<T>* sumar(const MatrizBase<T>& otra) const {
        std::cout << "(Suma manejada por MatrizEstatica)" << std::endl;
        
        if (this->_filas != otra.getFilas() || this->_columnas != otra.getColumnas()) {
            std::cout << "Error: No se pueden sumar matrices de diferentes dimensiones." << std::endl;
            return nullptr;
        }

        MatrizEstatica<T, M, N>* resultado = new MatrizEstatica<T, M, N>();

        for (int i = 0; i < this->_filas; i++) {
            for (int j = 0; j < this->_columnas; j++) {
                T val1 = this->get(i, j); 
                T val2 = otra.get(i, j);
                resultado->set(i, j, val1 + val2);
            }
        }

        return resultado;
    }
};


template <typename T>
MatrizBase<T>* operator+(const MatrizBase<T>& a, const MatrizBase<T>& b) {
    return a.sumar(b);
}


int main() {
    
    std::cout << "--- Sistema gérico de Álgebra Lineal --->" << std::endl;
    std::cout << ">> Demostración de Genericidad (Tipo FLOAT) <<" << std::endl << std::endl;

    MatrizBase<float>* A = new MatrizDinamica<float>(3, 2);
    A->cargarValores();
    A->imprimir();

    MatrizBase<float>* B = new MatrizEstatica<float, 3, 2>();
    B->cargarValores();
    B->imprimir();

    std::cout << "SUMANDO: Matriz C = A + B ..." << std::endl;
    
    MatrizBase<float>* C = *A + *B;
    
    if (C != nullptr) {
        std::cout << "Matriz Resultado C (3x2, Tipo FLOAT):" << std::endl;
        C->imprimir();
    }
    
    std::cout << std::endl;
    
    std::cout << ">> Demostración de Genericidad (Tipo INT) <<" << std::endl << std::endl;

    MatrizBase<int>* D = new MatrizDinamica<int>(2, 2);
    D->cargarValores(); 
    D->imprimir();

    MatrizBase<int>* E = new MatrizEstatica<int, 2, 2>();
    E->cargarValores(); 
    E->imprimir();
    
    std::cout << "SUMANDO: Matriz F = D + E ..." << std::endl;
    MatrizBase<int>* F = *D + *E; 
    
    if (F != nullptr) {
        std::cout << "Matriz Resultado F (2x2, Tipo INT):" << std::endl;
        F->imprimir();
    }

    
    std::cout << ">> Demostración de Limpieza de Memoria <<" << std::endl;
    
    std::cout << "Llamando al destructor de C..." << std::endl;
    delete C; 
    
    std::cout << "Llamando al destructor de A..." << std::endl;
    delete A; 
    
    std::cout << "Llamando al destructor de B..." << std::endl;
    delete B; 
    
    std::cout << "Llamando al destructor de F..." << std::endl;
    delete F; 

    std::cout << "Llamando al destructor de D..." << std::endl;
    delete D; 
    
    std::cout << "Llamando al destructor de E..." << std::endl;
    delete E; 
    
    std::cout << std::endl << "Sistema cerrado." << std::endl;

    return 0; 
}
