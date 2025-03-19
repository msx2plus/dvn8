#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

// its the little guy
void writeLittleEndian(unsigned int value, int numBytes, FILE * file) {
    unsigned char buffer[4];
    for (int i = 0; i < numBytes; ++i) {
        buffer[i] = value & 0xff;
        value >>= 8;
    }
    fwrite(buffer, numBytes, 1, file);
}

const char* mapToTarotCard(int value) {
    switch (value) {
        case 0:  return "the fool";
        case 1:  return "the magician";
        case 2:  return "the high priestess";
        case 3:  return "the empress";
        case 4:  return "the emperor";
        case 5:  return "the hierophant";
        case 6:  return "the lovers";
        case 7:  return "the chariot";
        case 8:  return "strength";
        case 9:  return "the hermit";
        case 10: return "wheel of fortune";
        case 11: return "justice";
        case 12: return "the hanged man";
        case 13: return "death";
        case 14: return "temperance";
        case 15: return "the devil";
        case 16: return "the tower";
        case 17: return "the star";
        case 18: return "the moon";
        case 19: return "the sun";
        case 20: return "judgement";
        case 21: return "the world";
        case 22: return "ace of wands";
        case 23: return "two of wands";
        case 24: return "three of wands";
        case 25: return "four of wands";
        case 26: return "five of wands";
        case 27: return "six of wands";
        case 28: return "seven of wands";
        case 29: return "eight of wands";
        case 30: return "nine of wands";
        case 31: return "ten of wands";
        case 32: return "page of wands";
        case 33: return "knight of wands";
        case 34: return "queen of wands";
        case 35: return "king of wands";
        case 36: return "ace of cups";
        case 37: return "two of cups";
        case 38: return "three of cups";
        case 39: return "four of cups";
        case 40: return "five of cups";
        case 41: return "six of cups";
        case 42: return "seven of cups";
        case 43: return "eight of cups";
        case 44: return "nine of cups";
        case 45: return "ten of cups";
        case 46: return "page of cups";
        case 47: return "knight of cups";
        case 48: return "queen of cups";
        case 49: return "king of cups";
        case 50: return "ace of swords";
        case 51: return "two of swords";
        case 52: return "three of swords";
        case 53: return "four of swords";
        case 54: return "five of swords";
        case 55: return "six of swords";
        case 56: return "seven of swords";
        case 57: return "eight of swords";
        case 58: return "nine of swords";
        case 59: return "ten of swords";
        case 60: return "page of swords";
        case 61: return "knight of swords";
        case 62: return "queen of swords";
        case 63: return "king of swords";
        case 64: return "ace of pentacles";
        case 65: return "two of pentacles";
        case 66: return "three of pentacles";
        case 67: return "four of pentacles";
        case 68: return "five of pentacles";
        case 69: return "six of pentacles";
        case 70: return "seven of pentacles";
        case 71: return "eight of pentacles";
        case 72: return "nine of pentacles";
        case 73: return "ten of pentacles";
        case 74: return "page of pentacles";
        case 75: return "knight of pentacles";
        case 76: return "queen of pentacles";
        case 77: return "king of pentacles";
        default: return "unknown card... probably an overflow";
    }
}

// quadratic easing
double quadraticEaseInOut(double t) {
    t *= 2;
    if (t < 1)
        return 0.5 * t * t;
    t--;
    return -0.5 * (t * (t - 2) - 1);
}

int main() {
    fprintf(stderr, "       />______ ____,__   _,_,   _,____ ________\n"
    "[######[] v0.1 (-|  (-\\\\  /(-|\\\\ |(-(__) by msx \\\n"
    "[######[]______ _|__/ _\\\\/  _| \\\\|,_(__)________/\n"
    "       \\>     (     (     (     (\n"
    "                                  `   \n");

    time_t currentTime;
    currentTime = time(NULL);
    int rightNow = (int) currentTime;

    int sample_rate = 8363;
    int mirror = 0;
    int samples = 32;
    int repetitions = 2;
    int interpolation = 0;
    int quad_offset = 0;
    int fun;

    printf("your number: ");
    scanf("%d", &fun);
            if (fun == 0) {
                fun = (rightNow * 1773 % 131070) + 131070; // i hit the juckport 1 trillion$
            }

    printf("mirror (0/1): ");
    scanf("%d", &mirror);
            if (mirror < 0) mirror = 0;
            if (mirror > 1) mirror = 1;

    printf("samples (8-1024): ");
    scanf("%d", &samples);
            if (samples < 8) samples = 8;
            if (samples > 1024) samples = 1024;

    printf("repeats (1-4): ");
    scanf("%d", &repetitions);
            if (repetitions < 1) repetitions = 1;
            if (repetitions > 4) repetitions = 4;

    printf("interpolation (0/1): ");
    scanf("%d", &interpolation);
            if (interpolation < 0) interpolation = 0;
            if (interpolation > 1) interpolation = 1;

    printf("interpolation jitter: ");
    scanf("%d", &quad_offset);
            if (quad_offset < 0) quad_offset = 0;

    sample_rate = (sample_rate*samples)/32;
    int adjusted_sample_rate = sample_rate * repetitions;

    FILE * file;
    char filename[50];
    sprintf(filename, "dvn8_n%d_s%d_r%d_m%d_i%d_j%d.wav", fun, samples, repetitions, mirror, interpolation, quad_offset);
    unsigned char buffer[samples];

    // hello
    file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "i can't do it for some reason!!!\n");
        return 1;
    }

    // some more crap
    double fun1 = fun % 555;
    double fun2 = fun % 777;
    double max_sample = 0;
    double min_sample = 0;
    double temp_buffer[samples];
    double more_temp_buffer[samples];
    bool reverse_flag = false;
    unsigned char min_val = buffer[0];
    unsigned char max_val = buffer[0];

    printf("now divining...\n");
    usleep(50000);

    // wave geneartion
    for (int i = 0; i < samples; i++) {
        double t = (double) i / sample_rate;
        int square = (int)(sin(2 * M_PI * (fun2 * 2) * 2 * t) >= 0 ? 1 : 0) * (fun1 / 333);
        double sine_value = 2.0 * (fabs(fmod(t * fun1, 1.0) - 0.5)) * sin(2 * M_PI * fun2 * t) + i * (fun2 / fun1 / 1000.0) + (cos(i * t * fun2) / (fun2 / 10)) + square;
        more_temp_buffer[i] = sine_value; //store it to a buffer
        max_sample = fmax(max_sample, sine_value); // sniffa da big
        min_sample = fmin(min_sample, sine_value); // sniffa da small
    }

    // sniffa is informed, get the difference
    double scale_factor = max_sample - min_sample;

    // generate using the calculated min/max and put into the real buffer
    for (int i = 0; i < samples; i++) {
        temp_buffer[i] = (more_temp_buffer[i] - min_sample)/scale_factor;
    }

    for (int i = 0; i < samples; i++) {
        if (!reverse_flag) {
            buffer[i] = (unsigned char)(255 * temp_buffer[i]); // forward
        } else {
            buffer[i] = (unsigned char)(255 * temp_buffer[samples - 1 - i]); // reverse
        }

    // mirror check
        if (i == samples / 2 - 1 && (mirror == 1)) {
            reverse_flag = true;
        }
    }

    // post-mirror normalization
    for (int i = 1; i < samples; i++) {
        if (buffer[i] < min_val) {
            min_val = buffer[i];
        }
        if (buffer[i] > max_val) {
            max_val = buffer[i];
        }
    }

    for (int i = 0; i < samples; i++) {
        buffer[i] = (unsigned char)((buffer[i] - min_val) * (255.0 / (max_val - min_val))); // write it!!!
    }

    // its a tarot application now
    int tarot_scale_factor = (int) round(scale_factor * fun) % 78;
    int tarot_max_sample = (int) round(max_sample * fun) % 78;
    int tarot_min_sample = (int) round(min_sample * fun) % 78;
    tarot_scale_factor = abs(tarot_scale_factor);
    tarot_max_sample = abs(tarot_max_sample);
    tarot_min_sample = abs(tarot_min_sample);
    bool reversed_scale_factor = tarot_scale_factor % 2 == 1;
    bool reversed_max_sample = tarot_max_sample % 2 == 1;
    bool reversed_min_sample = tarot_min_sample % 2 == 1;
    const char * tarot_card_scale_factor = mapToTarotCard(tarot_scale_factor);
    const char * tarot_card_max_sample = mapToTarotCard(tarot_max_sample);
    const char * tarot_card_min_sample = mapToTarotCard(tarot_min_sample);

    // wav header
    fprintf(file, "RIFF");
    writeLittleEndian(36 + samples * repetitions, 4, file); // chunk size
    fprintf(file, "WAVEfmt ");
    writeLittleEndian(16, 4, file); // chunk size
    writeLittleEndian(1, 2, file); // pcm
    writeLittleEndian(1, 2, file); // mono
    writeLittleEndian(adjusted_sample_rate, 4, file); // sample rate
    writeLittleEndian(adjusted_sample_rate, 4, file); // byte rate
    writeLittleEndian(1, 2, file); // block alignment
    writeLittleEndian(8, 2, file); // bits
    fprintf(file, "data");
    writeLittleEndian(samples * repetitions, 4, file); // data size

    // write samples
    if (interpolation == 1 && repetitions > 1) {
        for (int i = 0; i < samples; i++) {
            int idx1 = i;
            int idx2 = (i + 1 + (1 * quad_offset)) % samples; // wrap to first sample to calculate last interpolation step
            for (int j = 0; j < repetitions; j++) {
                double t = (double) j / repetitions;
                double easing_t = quadraticEaseInOut(t);
                double value = buffer[idx1] + (buffer[idx2] - buffer[idx1]) * easing_t;
                unsigned char sample = (unsigned char) value;
                fwrite( & sample, sizeof(unsigned char), 1, file);
            }
        }
    } else {
        for (int i = 0; i < samples; i++) {
            for (int j = 0; j < repetitions; j++) {
                fwrite( & buffer[i], sizeof(unsigned char), 1, file);
            }
        }
    }

    // get sample count
    int total_samples = samples * repetitions;

    // smpl chunk
    fprintf(file, "smpl");
    writeLittleEndian(60, 4, file); // chunk size
    writeLittleEndian(0, 4, file); // mfg
    writeLittleEndian(0, 4, file); // prod
    writeLittleEndian(0, 4, file); // s.pd
    writeLittleEndian(0, 4, file); // midi1
    writeLittleEndian(0, 4, file); // midi2
    writeLittleEndian(0, 4, file); // smpte1
    writeLittleEndian(0, 4, file); // smpte2
    writeLittleEndian(1, 4, file); // loops
    writeLittleEndian(0, 4, file); // sampler
    writeLittleEndian(0, 4, file); // cueid
    writeLittleEndian(0, 4, file); // type
    writeLittleEndian(0, 4, file); // start
    writeLittleEndian(total_samples, 4, file); // end
    writeLittleEndian(0, 4, file); // frac
    writeLittleEndian(0, 4, file); // count

    // check data size and adjust
    int data_size = total_samples * sizeof(unsigned char);
    fseek(file, 40, SEEK_SET); // move 2 data size
    writeLittleEndian(data_size, 4, file); // write size
    fseek(file, 4, SEEK_SET); // move 2 riff
    writeLittleEndian(36 + data_size + 68, 4, file); // write riff

    fclose(file);

    printf("the past: %s %s\n", tarot_card_scale_factor, reversed_scale_factor ? "(reversed)" : "");
    sleep(0.2);
    printf("the present: %s %s\n", tarot_card_max_sample, reversed_max_sample ? "(reversed)" : "");
    sleep(0.2);
    printf("the future: %s %s\n", tarot_card_min_sample, reversed_min_sample ? "(reversed)" : "");
    sleep(0.2);

    printf("generated '%s'\n", filename);

    printf("press a key to exit.\n");
    _getch();

    return 0;
}
