#include <stdio.h>
#include <math.h>

#define RADIUS_OF_EARTH 6371 // Raio médio da Terra em quilômetros

struct Point {
    double latitude;
    double longitude;
};

double to_radians(double degree) {
    return degree * (M_PI / 180.0);
}

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = to_radians(lat2 - lat1);
    double dlon = to_radians(lon2 - lon1);

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(to_radians(lat1)) * cos(to_radians(lat2)) *
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = RADIUS_OF_EARTH * c;
    return distance;
}

void find_points_within_radius(struct Point points[], int num_points, struct Point reference_point, double radius) {
    printf("Pontos dentro do raio de %.2lf km:\n", radius);
    for (int i = 0; i < num_points; i++) {
        double distance = calculate_distance(reference_point.latitude, reference_point.longitude,
                                             points[i].latitude, points[i].longitude);
        if (distance <= radius) {
            printf("Ponto %d: Latitude %.4lf, Longitude %.4lf\n", i+1, points[i].latitude, points[i].longitude);
        }
    }
}

int main() {
    struct Point points[] = {
        {41.3851, 2.1734},  // Barcelona
        {48.8566, 2.3522},  // Paris
        {51.5074, -0.1278}, // Londres
        {40.7128, -74.0060} // Nova York
        // Adicione mais pontos se necessário
    };
    int num_points = sizeof(points) / sizeof(points[0]);

    struct Point reference_point;
    printf("Digite a latitude do ponto de referência: ");
    scanf("%lf", &reference_point.latitude);
    printf("Digite a longitude do ponto de referência: ");
    scanf("%lf", &reference_point.longitude);

    double radius;
    printf("Digite o raio em quilômetros: ");
    scanf("%lf", &radius);

    find_points_within_radius(points, num_points, reference_point, radius);

    return 0;
}

