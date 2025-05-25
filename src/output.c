#include "output.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>



void plot_and_save_png(const ComplexFloat *iq_samples, size_t num_samples, const char *output_png_filename)
{
    float delta_plot = 0.5;
    MinMax min_max_im = get_min_max(&iq_samples->im, num_samples);
    MinMax min_max_re = get_min_max(&iq_samples->re, num_samples);
    float delta_plot_im =(min_max_im.max - min_max_im.min)*0.1;
    float delta_plot_re = (min_max_re.max - min_max_re.min)*0.1;
    FILE *gnuplotPipe = popen("gnuplot", "w");

    if (gnuplotPipe == NULL)
    {
        perror("Erro ao abrir pipe para o Gnuplot");
        return;
    }

    fprintf(gnuplotPipe, "set terminal pngcairo enhanced font \"arial,10\"\n");
    fprintf(gnuplotPipe, "set output \"%s\"\n", output_png_filename);
    fprintf(gnuplotPipe, "set title \"IQ\"\n");
    fprintf(gnuplotPipe, "set xlabel \"Re(I)\"\n");
    fprintf(gnuplotPipe, "set ylabel \"Im(Q)\"\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set tics out\n");
    fprintf(gnuplotPipe, "set key off\n");
    fprintf(gnuplotPipe, "set size square\n");
    fprintf(gnuplotPipe, "set xrange [%f:%f]\n", min_max_re.min - delta_plot_re, min_max_re.max + delta_plot_re);
    fprintf(gnuplotPipe, "set yrange [%f:%f]\n", min_max_im.min - delta_plot_im, min_max_im.max + delta_plot_im);

    fprintf(gnuplotPipe, "plot '-' with points pt 7 lc rgb \"blue\" title \"Símbolos\"\n");

    for (size_t i = 0; i < num_samples; i++)
    {
        fprintf(gnuplotPipe, "%g %g\n", iq_samples[i].re, iq_samples[i].im);
    }
    fprintf(gnuplotPipe, "e\n");
    fprintf(gnuplotPipe, "unset output\n");

    fflush(gnuplotPipe);
    pclose(gnuplotPipe);

    printf("Gráfico salvo em %s\n", output_png_filename);
}

int save_binary_to_file(const char *file_path, const unsigned int *bits_in, size_t num_bits)
{
    if (file_path == NULL || bits_in == NULL)
    {
        fprintf(stderr, "Error: Invalid arguments to save_binary_to_file (NULL path or bits).\n");
        return -1;
    }
    if (num_bits == 0)
    {
        fprintf(stderr, "Warning: No bits to save to file %s.\n", file_path);
        return 0;
    }

    FILE *file = fopen(file_path, "w");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        fprintf(stderr, "Error: Could not open file '%s' for writing binary data.\n", file_path);
        return -1;
    }

    for (size_t i = 0; i < num_bits; ++i)
    {
        if (fprintf(file, "%u\n", bits_in[i]) < 0)
        {
            fprintf(stderr, "Error writing bit %zu to file %s.\n", i, file_path);
            fclose(file);
            return -1;
        }
    }

    if (fclose(file) != 0)
    {
        perror("Error closing file after writing binary data");
        fprintf(stderr, "Error: Could not close file '%s' after writing.\n", file_path);
        return -1;
    }

    return 0;
}
