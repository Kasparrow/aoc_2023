#include <stdio.h>
#include <limits.h>
#include <pthread.h>

#define SEEDS_SIZE 20
#define INPUT_SIZE 192
#define SOURCE_SIZE 7

enum source { SEED, SOIL, FERTILIZER, WATER, LIGHT, TEMP, HUMIDITY };

struct thread_input {
    long* maps;
    int* sources_index;
    long seed_start;
    long seed_end;
    long result;
};

struct thread_input data[SEEDS_SIZE/2];

void scan_seeds(long* seeds);
void scan_map(long *maps, int *src_index);
long map_value(long *maps , enum source src, int* src_index, long value);
long seed_to_location(long *maps , int* src_index, long seed);

void* compute_seeds_range_closest_location(void* arg) {
    long i;
    long location, result;
    struct thread_input *data;
    data = (struct thread_input*) arg;

    result = LONG_MAX;

    for (i = data->seed_start; i < data->seed_end; ++i) {
        location = seed_to_location(data->maps, data->sources_index, i);
        result = location < result ? location : result;
    }
    data->result = result;
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    long maps[INPUT_SIZE*3], seeds[SEEDS_SIZE], result, location;
    long j;
    int sources_index[SOURCE_SIZE];
    int i;
    pthread_t ids[SEEDS_SIZE / 2];


    result = LONG_MAX;

    scan_seeds(seeds);
    scan_map(maps, sources_index);

    for (i = 0; i < SEEDS_SIZE; ++i) {
        location = seed_to_location(maps, sources_index, seeds[i]);
        result = location < result ? location : result;
    }

    printf("closest location : %ld\n", result);

    result = LONG_MAX;

    // shameless bruteforce (~4 minutes)
    for (i = 0; i < SEEDS_SIZE; i+=2) {
        data[i/2].maps = maps;
        data[i/2].sources_index = sources_index;
        data[i/2].seed_start = seeds[i];
        data[i/2].seed_end = seeds[i] + seeds[i+1];
        pthread_create(&ids[i/2], NULL, compute_seeds_range_closest_location, &data[i/2]);
    }

    for (i = 0; i < SEEDS_SIZE / 2; ++i) {
        pthread_join(ids[i], NULL);
    }

    for (i = 0; i < SEEDS_SIZE / 2; ++i) {
        result = result < data[i].result ? result : data[i].result;
    }

    printf("closest location (2) : %ld\n", result);

    return 0;
}

void scan_seeds(long* seeds) {
    int i;

    scanf("seeds: ");
    for(i = 0; i < SEEDS_SIZE; ++i) {
        scanf(" %ld", &seeds[i]);
    }

    // endline
    getchar();
    //emptyline
    getchar();

    scanf("seed-to-soil map:\n");
}

void scan_map(long *maps, int *src_index) {
    int i, dest_start, src_start, range, current_source, scan_res;
    char buffer[20];

    i = 0;
    current_source = SEED;
    src_index[current_source] = 0;

    while (1) {
        scan_res = scanf("%ld %ld %ld", &maps[i*3], &maps[i*3+1], &maps[i*3+2]);
        if (scan_res == 3) {
            ++i;
        } else if (scan_res == EOF) {
            return;
        } else {
            // new source maps
            src_index[++current_source] = i;
            // title
            scanf("%s map:\n", buffer);
        }
    }
}

long map_value(long *maps, enum source src, int* src_index, long value) {
    int i, max;

    max = src == SOURCE_SIZE - 1 ? INPUT_SIZE : src_index[src + 1];

    for (i = src_index[src]; i < max; ++i) {
        // small optimization allowed by the fact that the input have been sort
        if (value < maps[i*3+1])
            return value;
        if (value >= maps[i*3+1] && value < maps[i*3+1] + maps[i*3+2]) {
            return maps[i*3] + value - maps[i*3+1];
        }
    }

    return value;
}

long seed_to_location(long *maps, int* src_index, long seed) {
    long soil, fertilizer, water, light, temperature, humidity, location;

    soil = map_value(maps, SEED, src_index, seed);
    fertilizer = map_value(maps, SOIL, src_index, soil);
    water = map_value(maps, FERTILIZER, src_index, fertilizer);
    light = map_value(maps, WATER, src_index, water);
    temperature = map_value(maps, LIGHT, src_index, light);
    humidity = map_value(maps, TEMP, src_index, temperature);
    location = map_value(maps, HUMIDITY, src_index, humidity);

    return location;
}
