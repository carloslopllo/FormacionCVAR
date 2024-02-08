#include <deque>
class Filtro
{
public:
    virtual bool mean(float number, float &media) = 0;
};

class Mediamovil : public Filtro{
    private:
        int nvalor, contador;
        float suma;
        std::deque<float> dq;
    public:
        Mediamovil(int tamanno);
        bool mean(float number, float &media);
};