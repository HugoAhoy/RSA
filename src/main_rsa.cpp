#include "RSA.hpp"
#include "iostream"

int main(){
    std::ios::sync_with_stdio(false);
    std::string mode, e, d, n, content;
    long long key_length;
    long long part;
    while(std::cin >> mode){
        if(mode == "keygen"){
            std::cin >> key_length;
            Keys keys = GenerateKey(key_length);
            std::cout << keys.n.val() << std::endl;
            std::cout << keys.e.val() << std::endl;
            std::cout << keys.d.val() << std::endl;
        }
        else if(mode == "encrypt"){
            std::cin >> e >> n;
            std::cin >> part;
            while(part--){
                std::cin >> content;
                std::cout << Encrypt(e, n, content).val() << std::endl;
            }
        }
        else if(mode == "decrypt"){
            std::cin >> d >> n;
            std::cin >> part;
            while(part--){
                std::cin >> content;
                std::cout << Decrypt(d, n, content).val() << std::endl;
            }
        }
    }
    return 0;
}