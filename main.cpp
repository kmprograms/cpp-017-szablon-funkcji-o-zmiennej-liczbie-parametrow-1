#include <iostream>
#include <string>

// poczawszy od standardu C++ 11 mozemy tworzyc szablony o zmiennej liczbie
// parametrow

// typename ... T --> tak okreslamy pakiet parametrow szablonu
template <typename ... T>
// T ... args --> tak okreslamy pakiet argumentow funkcji
void fun1(T ... args) {
    // pozwala nam zwrocic w postaci stalej constexpr ile mamy w pakiecie zmiennych / typow
    std::cout << (sizeof...(T)) << std::endl;
}

// tutaj wersja gdzie pakiet parametrow szablonu nie jest jedyna pozycja w liscie argumentow
// mozesz umieszczac rowniez inne typy - dla pewnosci lepiej umieszczac pakiet parametrow
// szablonu na koncu chociaz teoretycznie kompilator moze poradzic sobie z pakietem szablonow
// umieszczonym w innym miejscu argumentow funkcji
template <typename U, typename ... T>
void fun2(U u, T ... args) {
    std::cout << u << std::endl;
    std::cout << (sizeof...(T)) << std::endl;
}

// klopotem podczas pracy z pakietem parametrow szablonu jest to ze nie ma wygodnej mozliwosci
// dostepu do elementow pakietu
// mozemy poradzic sobie z tym problemem kilka sposobów

// sposob 1

// ta funkcja jest potrzebna kiedy w funkcji get_params dochodzi do wywolania
// tej funkcji z zreowa liczba argumentow i to powoduje ze zostanie wywolana funkcja
// get_params() i ciag wywolan zostanie zakonczony
void get_params() {
    std::cout << "KONIEC" << std::endl;
}

// UWAGA!
// To nie jest czysta rekurencja poniewaz funkcja rekurencyjna wywolywalaby owszem siebie ale
// zawsze z taka sama iloscia parametrow a tutaj nie mamy takiej sytuacji bo za kazdym razem
// jest wolana jest funkcja o tej samej nazwie ale z innym zestawem argumentow
template <typename U, typename ... T>
void get_params(U u, T ... args) {
    std::cout << "WARTOSC: " << u  << " ROZMIAR: " << sizeof...(args) << std::endl;
    get_params(args...);
}

int main() {

    // wywolanie z <>
    fun1<std::string, int>("ADAM", 10);

    // wywolanie bez <>
    fun1("ADAM", 10);

    fun2<std::string, std::string, int>("A", "B", 10);

    fun2("A", "B", 10);

    get_params("ADAM", "EWA", 100, 200, 'A', 34.4);

    return 0;
}
