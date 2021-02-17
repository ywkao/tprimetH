#ifndef _toolbox_C_
#define _toolbox_C_

void print_values(TString name, double mean, double error);
double get_y_scope_max(TH1D* h, bool in_log_scale);
void estimate_mean_and_error(TH1D* h_sig, double &mean_signal, double &width_signal);


double get_y_scope_max(TH1D* h, bool in_log_scale)
{
    /* to be debugged */
    double max = h->GetMaximum();
    printf("[check] input = %.0f, ", max);
    
    double mantissa = 1.;
    int exponent = 0;
    while(max >= 1.)
    {
        max /= 10.;
        if(max > 1.)
        {
            mantissa = max;
            exponent += 1;
        }
    }

    mantissa = round(mantissa);
    max = mantissa * pow(10.0, (double) exponent);

    max = in_log_scale ? max*100. : max*1.2;
    printf("output = %.0f\n", max);
    return max;
}


void print_values(TString name, double mean, double error)
{
    printf("%s: mass = %.2f \\pm %.2f \n", name.Data(), mean, error);
}


void estimate_mean_and_error(TH1D* h_sig, double &mean_signal, double &width_signal)
{
    //--- Do the mean and width calculation ---//
    int bin_max = h_sig->GetMaximumBin();
    mean_signal = h_sig->GetBinCenter(bin_max);
    width_signal = 0.;
    double binW = h_sig->GetBinWidth(1);

    double all_integral = 0.;
    for(int i=1;i<(int)h_sig->GetNbinsX();++i)
        all_integral += h_sig->GetBinContent(i)*binW;

    double acc_integral = h_sig->GetBinContent(bin_max)*binW;
    for(int i=1;i<(int)h_sig->GetNbinsX();++i)
    {
        acc_integral += h_sig->GetBinContent(bin_max+i)*binW;
        acc_integral += h_sig->GetBinContent(bin_max-i)*binW;
        if( acc_integral/all_integral >= 0.682 ) {
            width_signal = h_sig->GetBinCenter(bin_max+i) - mean_signal;
            break;
        }
    }

    printf("[self] ratio = %.2f (%.2f/%.2f)\n", acc_integral/all_integral, acc_integral, all_integral );
    printf("[self] mass = %.2f \\pm %.2f\n", mean_signal, width_signal);
}

#endif
