#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(680, 680, "OpenGL Ornegi", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Dikey senkronizasyon (V-Sync) ayarlanýr

    const float DEG2RAD = 3.14159 / 180;
    const float aci = 0.2;
    const float triangleHeight = 0.4;
    const float triangleBase = 0.4;
    const float triangleOffset = 0.2;
    float x = 0.5;
    float y = -0.33;

    //Dairenin dikey ve yatay hareketi için
    bool ballLeft = true;
    bool ballDown = true;

    float hiz = 0.015;
    float triangleX = -0.5;
    float triangleY = 0.5;
    float triangleDX = 0.01;
    float triangleDY = -0.01;
    float r = 0.0;
    float g = 0.3;
    float b = 0.6;

    while (!glfwWindowShouldClose(window)) {        
        //çizim alanýnýn boyutu ayarlanýr ve arka plan temizlenir
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //Hareket - Daire        
        if (ballLeft) {
            if (x > -1 + aci) {
                x -= hiz;
            }
            else {
                ballLeft = false;
            }
        }
        else {
            if (x < 1 - aci) {
                x += hiz;
            }
            else {
                ballLeft = true;
            }
        }

        if (ballDown) {
            if (y > -1 + aci) {
                y -= hiz;
            }
            else {
                ballDown = false;
            }
        }
        else {
            if (y < 1 - aci) {
                y += hiz;
            }
            else {
                ballDown = true;
            }
        }

        //Hareket - Üçgen
        //Üçgenin hareketi güncellenir
        triangleX += triangleDX;
        triangleY += triangleDY;

        //Üçgenin kenarlara çarpma kontrolü
        if (triangleX - triangleBase / 2 < -1 || triangleX + triangleBase / 2 > 1) {
            triangleDX *= -1;
        }

        if (triangleY - triangleHeight / 2 < -1 || triangleY + triangleHeight / 2 > 1) {
            triangleDY *= -1;
        }

        //Çarpýþma kontrolü ve tepki
        float dx = triangleX - x;
        float dy = triangleY - y;
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < aci) {
            triangleDX *= -1;
            triangleDY *= -1;
        }

        //Renkler
        //fmod ile renk bileþenleri sýnýrlanýr
        r = fmod(r + 0.01, 1);
        g = fmod(g + 0.02, 1);
        b = fmod(b + 0.03, 1);

        //Çizim
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float degInRad = i * DEG2RAD;
            glColor3f(r, g, b);
            glVertex2f((cos(degInRad) * aci) + x, (sin(degInRad) * aci) + y);
        }
        glEnd();

        glBegin(GL_TRIANGLES);
        //Kýrmýzý renk
        glColor3f(1.0, 0.0, 0.0); 
        glVertex2f(triangleX, triangleY + triangleOffset);
        glVertex2f(triangleX - triangleBase / 2, triangleY - triangleHeight / 2);
        glVertex2f(triangleX + triangleBase / 2, triangleY - triangleHeight / 2);
        glEnd();

        //buffer'ý deðiþtirmek ve events kontrol etmek için
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Programýn sonlandýrlýmasý, pencerenin ve kütüphanenin kapatýlmasý için
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}