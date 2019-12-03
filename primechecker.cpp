#include "primechecker.h"

bool PrimeChecker::is_prime(size_t p)
{
    if(p==2)
    {
        return true;
    }
    if (p%2 == 0)
    {
        return false;
    }
    size_t limit = static_cast<size_t>(std::ceil(std::sqrt(p)));
    //sqrt(n)/2
    for (size_t i=3; i<=limit; i+=2)
    {
        if (p%i == 0)
        {
            return false;
        }
    }
    return true;
}

void PrimeChecker::read_commands()
{
    std::string inp;

    while (not exit)
    {
        std::cin >> inp;
        manage_input(inp);
    }
    {std::scoped_lock sl(q_acces);
        cv.notify_all();}
}

void PrimeChecker::check_prime(std::stop_token st)
{
    ++available_threads;
    while (not exit)
    {
        size_t n=0;

        {
        std::unique_lock ul(q_acces);
        cv.wait(ul, [this]{return not q.empty() or exit;});

        if (exit)
        {
            break;
        }

        //std::this_thread::sleep_for(std::chrono::seconds(1));
        n = q.front();
        q.pop();
        }

        --available_threads;
        size_t num = n_prime(n);
        ++available_threads;

        {
        std::scoped_lock l(out_mut);
        std::cout << n << ':' << num << std::endl;
        }
    }
}

void PrimeChecker::manage_input(const std::string &inp)
{
    try
    {
        size_t p = std::stoull(inp);
        if (inp.front() == '-')
        {
        	std::cerr << "Err: No se permiten numeros negativos\n";
        	return;
        }
		//std::cout << "Hilos recomendados: " << std::ceil(p*0.00000026) << std::endl;
	    std::scoped_lock sl(q_acces);
	    q.push(p);
    	cv.notify_one();
    }
    catch (std::invalid_argument&)
    {
        if (inp == "exit" or inp == "q")
        {
            exit = true;
        }
        else if (inp == "n")
        {
            std::scoped_lock l(out_mut);
            std::cout << "Hilos disponibles: " << available_threads << std::endl;
        }
        else
        {
            std::cerr << "Err: Argumento desconocido: " << inp << '\n';
        }
    }
    catch (std::out_of_range&)
    {
        std::cerr << "Err: Numero demasiado grande\n";
    }
}

size_t PrimeChecker::n_prime(size_t n) const
{
    size_t acc = 0;
    for (size_t i=3; i<=n and not exit; i+=2)
    {
        if (is_prime(i))
            ++acc;
    }
    return acc+1;
}
