#ifndef __TOOLBOX_H__
#define __TOOLBOX_H__
#include <TString.h>

struct My_Cut_Values{
    double bdt_nrb_lowerBound;
    double bdt_nrb_upperBound;

    double bdt_smh_lowerBound;
    double bdt_smh_upperBound;

    double mass_lowerBound;
    double mass_upperBound;
};

class Yield_Calculator {
    public:
        Yield_Calculator();
        virtual ~Yield_Calculator();
        virtual void Add(const double &weight);
        virtual void Report(TString tag);

    private:
        int entries;
        double yields;
        double sumW2;
        double uncertainty;
};

Yield_Calculator::Yield_Calculator()
{
    entries     = 0 ;
    yields      = 0.;
    sumW2       = 0.;
    uncertainty = 0.;
}

Yield_Calculator::~Yield_Calculator(){}

void Yield_Calculator::Add(const double &weight)
{
    entries++;
    yields += weight;
    sumW2 += weight*weight;
}

void Yield_Calculator::Report(TString tag)
{
    //printf(">>>>> Yield_Calculator::Report\n");
    uncertainty = sqrt(sumW2);
    printf("%s: %.2f \\pm %.2f\n", tag.Data(), yields, uncertainty);
}

#endif
