//Santiago Grande
//Emily Bonilla
//Santiago Figueroa

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

using namespace std;

const int MAX = 100;

char etiqueta[MAX];
int burst[MAX], arrival[MAX], queueId[MAX], priority[MAX];
int n = 0;

string FCFS(int n)
{
    string orden;

    int completion[MAX];
    int turnaround[MAX];
    int waiting[MAX];
    int response[MAX];

    bool ejecutado[MAX];

    for (int i = 0; i < n; i++)
    {
        ejecutado[i] = false;
        completion[i] = 0;
        turnaround[i] = 0;
        waiting[i] = 0;
        response[i] = 0;
    }

    int tiempo = 0;
    int completados = 0;

    cout << "\n--- Timeline ---\n";

    while (completados < n)
    {
        int indiceProceso = -1;
        int menorArrival = 1000000;

        for (int i = 0; i < n; i++)
        {
            if (ejecutado[i] == false)
            {
                if (arrival[i] <= tiempo)
                {
                    if (arrival[i] < menorArrival)
                    {
                        menorArrival = arrival[i];
                        indiceProceso = i;
                    }
                }
            }
        }

        if (indiceProceso == -1)
        {
            tiempo = tiempo + 1;
        }
        else
        {
            int inicio = tiempo;

            response[indiceProceso] = inicio - arrival[indiceProceso];

            cout << "t=" << tiempo << " -> " << etiqueta[indiceProceso];

            tiempo = tiempo + burst[indiceProceso];

            cout << " -> t=" << tiempo << endl;

            completion[indiceProceso] = tiempo;
            ejecutado[indiceProceso] = true;
            completados = completados + 1;

            orden.push_back(etiqueta[indiceProceso]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    cout << "\n--- Resultados ---\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++)
    {
        cout << etiqueta[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t"
             << turnaround[i] << "\t"
             << waiting[i] << "\t"
             << response[i] << endl;
    }

    return orden;
}

string SJF(int n)
{
    string orden;

    int completion[MAX];
    int turnaround[MAX];
    int waiting[MAX];
    int response[MAX];

    bool ejecutado[MAX];

    for (int i = 0; i < n; i++)
    {
        ejecutado[i] = false;
        completion[i] = 0;
        turnaround[i] = 0;
        waiting[i] = 0;
        response[i] = 0;
    }

    int tiempo = 0;
    int completados = 0;

    cout << "\n--- Timeline ---\n";

    while (completados < n)
    {
        int indiceProceso = -1;
        int menorBurst = 1000000;

        for (int i = 0; i < n; i++)
        {
            if (ejecutado[i] == false)
            {
                if (arrival[i] <= tiempo)
                {
                    if (burst[i] < menorBurst)
                    {
                        menorBurst = burst[i];
                        indiceProceso = i;
                    }
                }
            }
        }

        if (indiceProceso == -1)
        {
            tiempo = tiempo + 1;
        }
        else
        {
            int inicio = tiempo;

            response[indiceProceso] = inicio - arrival[indiceProceso];

            cout << "t=" << tiempo << " -> " << etiqueta[indiceProceso];

            tiempo = tiempo + burst[indiceProceso];

            cout << " -> t=" << tiempo << endl;

            completion[indiceProceso] = tiempo;
            ejecutado[indiceProceso] = true;
            completados = completados + 1;

            orden.push_back(etiqueta[indiceProceso]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    cout << "\n--- Resultados ---\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++)
    {
        cout << etiqueta[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t"
             << turnaround[i] << "\t"
             << waiting[i] << "\t"
             << response[i] << endl;
    }

    return orden;
}

string RR(int quantum, int n)
{
    deque<int> cola;
    string orden;

    bool enCola[MAX];
    int restante[MAX];
    int completion[MAX];
    int turnaround[MAX];
    int waiting[MAX];
    int response[MAX];
    bool inicio[MAX];

    // Inicialización
    for (int i = 0; i < n; i++)
    {
        restante[i] = burst[i];
        enCola[i] = false;
        inicio[i] = false;
        completion[i] = 0;
        turnaround[i] = 0;
        waiting[i] = 0;
        response[i] = 0;
    }

    int tiempo = 0;
    int completados = 0;

    cout << "\n--- Timeline ---\n";

    while (completados < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (arrival[i] <= tiempo && restante[i] > 0 && enCola[i] == false)
            {
                cola.push_back(i);
                enCola[i] = true;
            }
        }

        if (cola.empty())
        {
            tiempo = tiempo + 1;
        }
        else
        {
            int indiceProceso = cola.front();
            cola.pop_front();

            if (inicio[indiceProceso] == false)
            {
                response[indiceProceso] = tiempo - arrival[indiceProceso];
                inicio[indiceProceso] = true;
            }

            int tiempoEjecucion = min(quantum, restante[indiceProceso]);

            cout << "t=" << tiempo << " -> " << etiqueta[indiceProceso];

            restante[indiceProceso] = restante[indiceProceso] - tiempoEjecucion;
            tiempo = tiempo + tiempoEjecucion;

            cout << " -> t=" << tiempo << endl;

            orden.push_back(etiqueta[indiceProceso]);

            for (int j = 0; j < n; j++)
            {
                if (arrival[j] <= tiempo && restante[j] > 0 && enCola[j] == false)
                {
                    cola.push_back(j);
                    enCola[j] = true;
                }
            }

            if (restante[indiceProceso] > 0)
            {
                cola.push_back(indiceProceso);
            }
            else
            {
                completion[indiceProceso] = tiempo;
                completados = completados + 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    cout << "\n--- Resultados ---\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++)
    {
        cout << etiqueta[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t"
             << turnaround[i] << "\t"
             << waiting[i] << "\t"
             << response[i] << endl;
    }

    return orden;
}

string PSJF(int n)
{
    string orden;

    int restante[MAX];
    int completion[MAX];
    int turnaround[MAX];
    int waiting[MAX];
    int response[MAX];
    bool inicio[MAX];

    for (int i = 0; i < n; i++)
    {
        restante[i] = burst[i];
        completion[i] = 0;
        turnaround[i] = 0;
        waiting[i] = 0;
        response[i] = 0;
        inicio[i] = false;
    }

    int tiempo = 0;
    int completados = 0;
    int procesoActual = -1;
    int inicioSegmento = 0;

    cout << "\n--- Timeline ---\n";

    while (completados < n)
    {
        int indiceProceso = -1;
        int menorRestante = 1000000;

        if (procesoActual != -1)
        {
            if (arrival[procesoActual] <= tiempo && restante[procesoActual] > 0)
            {
                indiceProceso = procesoActual;
                menorRestante = restante[procesoActual];
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (arrival[i] <= tiempo && restante[i] > 0)
            {
                if (restante[i] < menorRestante)
                {
                    menorRestante = restante[i];
                    indiceProceso = i;
                }
                else if (restante[i] == menorRestante)
                {
                    if (indiceProceso == -1)
                    {
                        indiceProceso = i;
                    }
                    else if (indiceProceso != procesoActual)
                    {
                        if (arrival[i] < arrival[indiceProceso])
                        {
                            indiceProceso = i;
                        }
                    }
                }
            }
        }

        if (indiceProceso == -1)
        {
            tiempo = tiempo + 1;
        }
        else
        {
            if (procesoActual != indiceProceso)
            {
                if (procesoActual != -1)
                {
                    cout << "t=" << inicioSegmento << " -> " << etiqueta[procesoActual] << " -> t=" << tiempo << endl;
                    orden.push_back(etiqueta[procesoActual]);
                }

                procesoActual = indiceProceso;
                inicioSegmento = tiempo;

                if (inicio[indiceProceso] == false)
                {
                    response[indiceProceso] = tiempo - arrival[indiceProceso];
                    inicio[indiceProceso] = true;
                }
            }

            restante[indiceProceso] = restante[indiceProceso] - 1;
            tiempo = tiempo + 1;

            if (restante[indiceProceso] == 0)
            {
                completion[indiceProceso] = tiempo;
                completados = completados + 1;

                cout << "t=" << inicioSegmento << " -> " << etiqueta[indiceProceso] << " -> t=" << tiempo << endl;
                orden.push_back(etiqueta[indiceProceso]);

                procesoActual = -1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
    }

    cout << "\n--- Resultados ---\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++)
    {
        cout << etiqueta[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t"
             << turnaround[i] << "\t"
             << waiting[i] << "\t"
             << response[i] << endl;
    }

    return orden;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Uso: ./programa archivo algoritmo [quantum] {para RR}" << endl;
    }
    else
    {
        string nombreArchivo = argv[1];
        string algoritmo = argv[2];
        int quantum = 0;

        if (algoritmo == "RR")
        {
            if (argc < 4)
            {
                cout << "Error: RR necesita quantum" << endl;
            }
            else
            {
                stringstream ss(argv[3]);
                ss >> quantum;
            }
        }
        if(algoritmo == "FCFS")
        {

        }

        ifstream archivo(nombreArchivo.c_str());

        if (!archivo.is_open())
        {
            cout << "Error al abrir archivo" << endl;
        }
        else
        {
            string linea;

            while (getline(archivo, linea))
            {
                if (linea.size() > 0 && linea[0] != '#')
                {
                    stringstream ss(linea);
                    string token;

                    getline(ss, token, ';');
                    etiqueta[n] = token[0];

                    getline(ss, token, ';');
                    stringstream s2(token);
                    s2 >> burst[n];

                    getline(ss, token, ';');
                    stringstream s3(token);
                    s3 >> arrival[n];

                    getline(ss, token, ';');
                    stringstream s4(token);
                    s4 >> queueId[n];

                    getline(ss, token, ';');
                    stringstream s5(token);
                    s5 >> priority[n];

                    n = n + 1;
                }
            }

            archivo.close();

            if (algoritmo == "RR")
            {
                string resultado = RR(quantum, n);
                cout << "Orden de ejecucion: " << resultado << endl;
            }
            else if (algoritmo == "FCFS")
            {
                string resultado = FCFS(n);
                cout << "Orden de ejecucion: " << resultado << endl;

            }
            else if (algoritmo == "SJF")
            {
                string resultado = SJF(n);
                cout << "Orden de ejecucion: " << resultado << endl;

            }
            else if (algoritmo == "PSJF")
            {
                string resultado = PSJF(n);
                cout << "Orden de ejecucion: " << resultado << endl;
            }
            else
            {
                cout << "Algoritmo no reconocido" << endl;
            }
        }
    }

    return 0;
}