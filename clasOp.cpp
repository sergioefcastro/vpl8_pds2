#include <iostream>
#include <list>
#include <iterator>

class Objeto {
private:
    int id;
    static int proxId;
    static int totalObjetos;

public:
    // Construtor com id automático
    Objeto() {
        id = proxId++;
        totalObjetos++;
    }

    // Construtor com id fornecido
    Objeto(int idPersonalizado) {
        if (idPersonalizado < 0) {
            id = idPersonalizado;
        } else {
            id = proxId++;
        }
        totalObjetos++;
    }

    // Destrutor
    ~Objeto() {
        totalObjetos--;
    }

    // Método para retornar o id do objeto
    int getId() const {
        return id;
    }

    // Método para retornar o número de objetos existentes
    static int getTotalObjetos() {
        return totalObjetos;
    }

    // Método para retornar o endereço de memória do objeto
    const Objeto* getEndereco() const {
        return this;
    }
};

// Inicialização dos membros estáticos
int Objeto::proxId = 1;
int Objeto::totalObjetos = 0;

int main() {
    std::list<Objeto*> lista;
    char comando;
    
    while (std::cin >> comando) {
        if (comando == 'A') {
            Objeto* novo = new Objeto();
            lista.push_back(novo);
            std::cout << novo->getId() << " " << novo->getEndereco() << std::endl;
        }
        else if (comando == 'C') {
            int idPersonalizado;
            std::cin >> idPersonalizado;
            if (idPersonalizado < 0) {
                Objeto* novo = new Objeto(idPersonalizado);
                lista.push_front(novo);
                std::cout << novo->getId() << " " << novo->getEndereco() << std::endl;
            } else {
                std::cout << "ERRO" << std::endl;
            }
        }
        else if (comando == 'R') {
            if (!lista.empty()) {
                Objeto* obj = lista.front();
                lista.pop_front();
                std::cout << obj->getId() << " " << obj->getEndereco() << std::endl;
                delete obj;
            } else {
                std::cout << "ERRO" << std::endl;
            }
        }
        else if (comando == 'N') {
            std::cout << Objeto::getTotalObjetos() << std::endl;
        }
        else if (comando == 'P') {
            int indice;
            std::cin >> indice;
            if (indice > 0 && indice <= lista.size()) {
                auto it = lista.begin();
                std::advance(it, indice - 1);
                std::cout << (*it)->getId() << " " << (*it)->getEndereco() << std::endl;
            } else {
                std::cout << "ERRO" << std::endl;
            }
        }
        else if (comando == 'L') {
            for (const auto& obj : lista) {
                std::cout << obj->getId() << " " << obj->getEndereco() << std::endl;
            }
        }
        else if (comando == 'E') {
            break;
        }
    }

    // Libera memória dos objetos restantes
    for (const auto& obj : lista) {
        delete obj;
    }

    return 0;
}
