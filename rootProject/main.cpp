#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cmath>
#include <iostream>
#include <vector>

double y(double x) { return 2.4 * x * x * x + 4.4 * x * x - 2 * x + 1.5; }
double yprime(double x) { return 3 * 2.4 * x * x + 8.8 * x - 2; }

double secantmethod(double x0, double x1, double tolerance) {
    double x = x1;
    while (fabs(y(x)) > tolerance) {
        x = x1 - y(x1) * (x1 - x0) / (y(x1) - y(x0));
        x0 = x1;
        x1 = x;
    }
    return x;
}

double newtonRaphson(double x0, double tolerance) {
    double x = x0;
    while (fabs(y(x)) > tolerance) {
        x = x0 - (y(x0) / yprime(x0));
        x0 = x;
    }
    return x;
}

double bisection(double a, double b, double tolerance) {
    double x = a;
    if (y(a) * y(b) >= 0) {
        return NAN; // invalid range
    } else {
        while (fabs(y(x)) > tolerance) {
            x = (a + b) / 2;
            if (y(x) * y(a) < 0)
                b = x;
            else
                a = x;
        }
        return x;
    }
}

int main(int, char**) {
    // --- SDL + ImGui init ---
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_Window* window = SDL_CreateWindow("Root Finder GUI", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 900, 700,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool done = false;
    int method = 0; // 0=Secant, 1=Newton-Raphson, 2=Bisection
    double x0 = 0.0, x1 = 0.0, a = 0.0, b = 0.0, tolerance = 1e-6;
    double result = NAN;
    bool computed = false;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Root Finder");

        ImGui::Text("Select the method:");
        const char* methods[] = {"Secant Method", "Newton-Raphson", "Bisection Method"};
        ImGui::Combo("##Method", &method, methods, IM_ARRAYSIZE(methods));

        ImGui::Separator();

        // Show input fields depending on method
        if (method == 0) {
            ImGui::InputDouble("x0", &x0);
            ImGui::InputDouble("x1", &x1);
        } else if (method == 1) {
            ImGui::InputDouble("Initial guess x0", &x0);
        } else if (method == 2) {
            ImGui::InputDouble("Lower bound a", &a);
            ImGui::InputDouble("Upper bound b", &b);
        }
        ImGui::InputDouble("Tolerance", &tolerance);

        if (ImGui::Button("Compute Root")) {
            if (method == 0)
                result = secantmethod(x0, x1, tolerance);
            else if (method == 1)
                result = newtonRaphson(x0, tolerance);
            else if (method == 2)
                result = bisection(a, b, tolerance);
            computed = true;
        }

        if (computed) {
            if (std::isnan(result))
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid interval or computation failed.");
            else
                ImGui::Text("Root ≈ %.8f", result);
        }

        ImGui::Separator();
        if (ImPlot::BeginPlot("f(x) = 2.4x³ + 4.4x² - 2x + 1.5")) {
            static std::vector<double> X(200), Y(200);
            double xmin = -5.0, xmax = 5.0;
            for (int i = 0; i < 200; i++) {
                X[i] = xmin + i * (xmax - xmin) / 199.0;
                Y[i] = y(X[i]);
            }
            ImPlot::PlotLine("f(x)", X.data(), Y.data(), (int)X.size());
            if (computed && !std::isnan(result)) {
                double fx = y(result);
                ImPlot::PlotScatter("Root", &result, &fx, 1);
            }
            ImPlot::EndPlot();
        }

        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

