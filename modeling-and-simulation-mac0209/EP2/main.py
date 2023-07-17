#obrigatorios
from kivy.app import App
from kivy.lang import Builder

#lib do plyer
from plyer import accelerometer
#from plyer import gravity
from kivy.clock import Clock

#libs do grafico
import numpy as np
from kivy_garden.graph import Graph, LinePlot, MeshLinePlot
#import pandas as pd
#from matplotlib import pyplot as plt
#from scipy.signal import find_peaks

#libs do kivy
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.core.window import Window
from kivy.uix.popup import Popup
from kivy.uix.textinput import TextInput

#Builder.load_file("main.kv")

# GERAIS
class Gerenciador(ScreenManager):
    pass

class Menu(Screen):
    pass

# ACELEROMETRO
class PhysicsScreen(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.telaGrafico = Physics();

        self.add_widget(self.telaGrafico)

    def on_pre_enter(self):
        Window.bind(on_keyboard=self.voltar)

    def voltar(self,window,key,*args):
        if key == 27:
            App.get_running_app().root.current = 'menu'
            return True

    def on_pre_leave(self):
        Window.unbind(on_keyboard=self.voltar)

class Physics(BoxLayout):
    def __init__(self,**kwargs):
        super().__init__(**kwargs)

        self.valorG = 9.806

        #incia o vetor das forcas
        self.accelX = []
        self.accelY = []
        self.accelZ = []
        self.tempo = []
        self.tfg = []

        self.data = []

        #configuracoes do grafico
        self.time_list = []
        self.time_counter = 0
        self.time_step = 0.1
        self.xmax_plot = 50
        self.xmin_plot = 0
        self.ymax_plot = 5
        self.ymin_plot = -5
        self.graph = None
        self.plot = None
        self.plotEixos = []
        self.start_function = None
        self.incia_plot()

        App.dadosCaptados = False

    def incia_plot(self):

        graph_theme = {
            'label_options':{
                'color':[0,0,0,1]
            }
        }
        self.graph = Graph(xmin=self.xmin_plot, xmax=self.xmax_plot, ymin=self.ymin_plot, ymax=self.ymax_plot,  
                           border_color=[0, 0, 0, .4],
                           x_grid=True, y_grid=True,
                           draw_border=True,xlabel='Tempo',ylabel='G-Force',
                           x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 5,
                           y_ticks_minor = 1,y_ticks_major = 1,
                           y_grid_label=True,
                           **graph_theme)
        
        self.graph.background_color = 1, 1, 1, 1
        
        self.ids.box.add_widget(self.graph)

        # mesmas cores do physics toolbox (X - Vermelho, Y - Verde, Z - Azul e G - branco)
        self.plotEixos.append(MeshLinePlot(color=[1, 0, 0, 1])) 
        self.plotEixos.append(MeshLinePlot(color=[0, 1, 0, 1]))     
        self.plotEixos.append(MeshLinePlot(color=[0, 0, 1, 1]))
        self.plotEixos.append(MeshLinePlot(color=[0, 0, 0, 1]))

        self.reset_plot()

        # adiciona todos os plots no grafico
        for i in self.plotEixos:
            self.graph.add_plot(i)

    def update_label(self, *args):
        dados = accelerometer.acceleration[:3]
        
        self.time_list.append(self.time_counter)
        self.time_counter += self.time_step

        if self.time_counter > self.xmax_plot:
            self.reset_plot()
        if not dados == (None, None, None):
            self.tempo.append(self.time_counter)
            self.plotEixos[0].points.append((self.time_counter, dados[0]/self.valorG))
            self.plotEixos[1].points.append((self.time_counter, dados[1]/self.valorG))
            self.plotEixos[2].points.append((self.time_counter, dados[2]/self.valorG))
            self.plotEixos[3].points.append((self.time_counter, (dados[0]*dados[0] + dados[1]*dados[1] + dados[2]*dados[2])**0.5/self.valorG))

    def start(self):

        # ativa o acelerometro e os sensores
        accelerometer.enable()

        self.start_function = Clock.schedule_interval(self.update_label, self.time_step)

    def stop(self):
        if self.start_function:
            self.start_function.cancel()
            # desativa o acelerometro
            accelerometer.disable()


    def clear_plot(self):
        self.ids.box.clear_widgets()
        self.incia_plot()
        self.reset_plot()

    def reset_plot(self):
        for i in self.plotEixos:
            i.points = [(0, 0)]
        self.time_counter = 0
        self.time_list = []

    def save(self):
        App.accelX = self.plotEixos[0].points
        App.accelY = self.plotEixos[1].points
        App.accelZ = self.plotEixos[2].points
        App.tfg = self.plotEixos[3].points
        App.dadosCaptados = True
        
        
    def show_popup(self):
        p = Aviso1()
        p.open()

    def returnVector(self):
        if(App.dadosCaptados == False):
            p = Aviso2()
            p.open()

            return 0, 0, 0, 0
        
        else:
            return App.accelX, App.accelY, App.accelZ, App.tfg

# PLOTAGEM
class MenuPlota(Screen):
    pass 

    def on_pre_enter(self):
        Window.bind(on_keyboard=self.voltar)

    def voltar(self,window,key,*args):
        if key == 27:
            App.get_running_app().root.current = 'menu'
            return True

    def on_pre_leave(self):
        Window.unbind(on_keyboard=self.voltar)

class MUScreen(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.telaMU = MU();

        self.add_widget(self.telaMU)

    def on_pre_enter(self):
        Window.bind(on_keyboard=self.voltar)

    def voltar(self,window,key,*args):
        if key == 27:
            App.get_running_app().root.current = 'menuPlota'
            return True

    def on_pre_leave(self):
        Window.unbind(on_keyboard=self.voltar)

class MU(BoxLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.graph_theme = {
            'label_options':{
                'color':[0,0,0,1]
            }
        }
        self.graficoPos = Graph(xmin=0, xmax=1, ymin=0, ymax=10,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                x_grid=True, y_grid=True,
                                draw_border=True,xlabel='Tempo (s)',ylabel='Espaço (m)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 5,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)
        
        self.analticoPlot = MeshLinePlot(color=[1,0,0,1])
        self.analticoPlot.points = [(0,0)]
        self.eulerPlot = MeshLinePlot(color=[0,1,0,1])
        self.eulerPlot.points = [(0,0)]

        self.ids.graph.add_widget(self.graficoPos)
        self.graficoPos.add_plot(self.analticoPlot)
        self.graficoPos.add_plot(self.eulerPlot)

    def addTempoMU(self):
        self.tempoTotalMU = (float)(self.ids.tempoMU.text)

    def addPassosMU(self):
        self.passosTotalMU = (float)(self.ids.passosMU.text)

    def addTamPassosMU(self):
        self.tamPassosMU = (float)(self.ids.tamPassosMU.text)

    def V(self):
        return self.velocidade  # calculado com base nos dados do experimento

    def espacoAnalitico(self, t):
        return (self.V() * t)

    def espacoEuler(self, dt, v):
        return(v*dt)    
    
    def gerarGraficoMU(self):
        """ self.dataX, self.dataY, self.dataZ, self.dataG = Physics.returnVector(self)

        if(self.dataX == 0):
            return 
        else:
            p = Aviso3()
            p.open() """

        #metadados
        captureRate = 100 #captura dos dados no app
        dt = 0.1
        xAnda = []
        yAnda = []

        #variaveis
        soma = [0]
        duracaoExperimentos = 0
        passos = self.addPassosMU()
        vxe = []
        vxa = []

        #plotagem
        self.plotEixos = []

        #plot da gravacao inteira
        #peaks, _ = find_peaks(self.dataY, distance=10, prominence=0.5)
        
        """ fig, ax = plt.subplots()
        plt.plot(x, y)
        plt.title('Dados do acelerometro')
        ax.set_xlabel('Tempo (segundos)')
        ax.set_ylabel('Resultante (forca g)')
        plt.show() """

        # print dos corte
        #for count in range(3):
        #    duracaoExperimentos = duracaoExperimentos + self.dataX[(peaks[passos*(count+1)-1])] - self.dataX[(peaks[passos*count])]
        """ fig, ax = plt.subplots()
            plt.plot(self.dataX[(peaks[passos*count]) - 150 : (peaks[(passos*(count+1))-1]) + 150], self.dataY[(peaks[passos*count]) - 150 : (peaks[(passos*(count+1))-1]) + 150])
            # , marker = "x", linestyle="", label = "passos"
            plt.title(f'Dados da caminhada {count+1}')
            ax.set_xlabel('Tempo (segundos)')
            ax.set_ylabel('Resultante (forca g)')
            plt.show()
            xAnda.append(self.dataX[(peaks[passos*count]) - 150 : (peaks[passos*(count)]) + 1100])
            yAnda.append(self.dataY[(peaks[passos*count]) - 150 : (peaks[passos*(count)]) + 1100]) """

        self.addTempoMU()
        self.addPassosMU()
        self.addTamPassosMU()

        tempoExperimento = self.tempoTotalMU
        
        distanciaAndada = self.passosTotalMU * self.tamPassosMU
        self.velocidade = (distanciaAndada/tempoExperimento)

        #caminhada média
        """ for i in range(3):
            soma = soma + yAnda[i]

        yMedio = (soma/5)

        fig, ax = plt.subplots()
        plt.plot(xAnda[0], yMedio)               #ajuste pro tempo de começo da gravação
        plt.title('Caminhada Média')
        ax.set_xlabel('Tempo (segundos)')
        ax.set_ylabel('Resultante (forca g)')
        plt.show() """

        self.ids.graph.remove_widget(self.graficoPos)
        self.analticoPlot.points = [(0,0)]
        self.eulerPlot.points = [(0,0)]

        t = 0
        tf = tempoExperimento
        posicaoE = 0

        while(t < tf):
            posicaoA = self.espacoAnalitico(t)
            posicaoE = self.espacoEuler(t, self.velocidade)
            self.analticoPlot.points.append((t,posicaoA))
            self.eulerPlot.points.append((t,posicaoE))
            t = t + dt
            vxa.append(posicaoA)
            vxe.append(posicaoE)

        yMax = posicaoA + 1


        self.graficoPos = Graph(xmin=0, xmax=self.tempoTotalMU, ymin=0,ymax = yMax,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                draw_border=True,xlabel='Tempo (s)',ylabel='Espaço (m)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 5,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme) 

        self.ids.graph.add_widget(self.graficoPos)
        self.graficoPos.add_plot(self.analticoPlot)
        self.graficoPos.add_plot(self.eulerPlot)

class MUVScreen(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.telaMUV = MUV();

        self.add_widget(self.telaMUV)

    def on_pre_enter(self):
        Window.bind(on_keyboard=self.voltar)

    def voltar(self,window,key,*args):
        if key == 27:
            App.get_running_app().root.current = 'menuPlota'
            return True

    def on_pre_leave(self):
        Window.unbind(on_keyboard=self.voltar)

class MUV(BoxLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.graph_theme = {
            'label_options':{
                'color':[0,0,0,1]
            }
        }
        self.graficoPos = Graph(xmin=0, xmax=1, ymin=0, ymax=10,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                x_grid=True, y_grid=True,
                                draw_border=True,xlabel='Tempo (s)',ylabel='Espaço (m)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)
        
        self.analticoPlot = MeshLinePlot(color=[1,0,0,1])
        self.analticoPlot.points = [(0,0)]
        self.eulerPlot = MeshLinePlot(color=[0,1,0,1])
        self.eulerPlot.points = [(0,0)]

        self.ids.graph.add_widget(self.graficoPos)
        self.graficoPos.add_plot(self.analticoPlot)
        self.graficoPos.add_plot(self.eulerPlot)

        self.graficoVel = Graph(xmin=0, xmax=1, ymin=0, ymax=10,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                x_grid=True, y_grid=True,
                                draw_border=True,xlabel='Tempo (s)',ylabel='Velocidade (m/s)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)

        self.velPlot = MeshLinePlot(color=[1,0,0,1])
        self.velPlot.points = [(0,0)]

        self.ids.graph.add_widget(self.graficoVel)
        self.graficoVel.add_plot(self.velPlot)

    def addTempoMUV(self):
        self.tempoTotalMUV = (float)(self.ids.tempoMUV.text)

    def addPassosMUV(self):
        self.passosTotalMUV = (float)(self.ids.passosMUV.text)

    def addTamPassosMUV(self):
        self.tamPassosMUV = (float)(self.ids.tamPassosMUV.text)

    def posicaoAnaliticoMUV(self, v0, dt, a, t):
        return (v0*t+(a*dt*t))

    def velocidadeMUV(self, a, v0, dt):
        return (v0+a*dt)

    def posicaoEulerMUV(self, s0, v0, dt, a):
        return (s0 + (v0 + a*dt)*dt)

    def gerarGraficoMUV(self):

        """ self.dataX, self.dataY, self.dataZ, self.dataG = Physics.returnVector(self)
        if(self.dataX == 0):
            return 
        else:
            p = Aviso3()
            p.open()
        
        passos = self.addPassosMUV() """

        """ fig, ax = plt.subplots()
        plt.plot(x,y)
        plt.title('Dados do acelerometro')
        ax.set_xlabel('Tempo (segundos)')
        ax.set_ylabel('Resultante (forca g)')
        plt.show() """

        """ cont = 0
        somaVelFinalMedia = 0
        somaTTotalMedio = 0
        yCaminhada = [] """
        #plota corte s
        """ while (cont < 3):
            if (cont != 2):
                x = data[(1 + cont * passos)* captureRate : (11 + cont * passos)* captureRate,0]
                y = data[(1 + cont * passos)* captureRate : (11 + cont * passos)* captureRate,4]
            else:
                x = data[(2 + cont * passos)* captureRate : (10 + cont * passos)* captureRate,0]
                y = data[(2 + cont * passos)* captureRate : (10 + cont * passos)* captureRate,4]
          
            # procura picos
            #prominence maior vai detectar picos maiores
            peaks, _ = find_peaks(y, distance=15, prominence=0.15)

            #pego a Caminhada Normalizada a partir de um pouco antes do primeiro passo
            # para calcular a caminhada media
            yCaminhada.append(self.dataY[peaks[0]- 60 : peaks[0] + 600])

            fig, ax = plt.subplots()
            plt.plot(x,y)
            plt.plot(self.dataX[peaks], self.dataY[peaks], marker = "x", linestyle="", label = "passos")
            plt.title(f'Dados da caminhada {cont+1}')
            ax.set_xlabel('Tempo (segundos)')
            ax.set_ylabel('Resultante (forca g)')
            plt.legend(loc = "upper right")
            plt.show()

            cont += 1
            #calcula Velocidade final média
            t = self.dataX[peaks[11]] - self.dataX[peaks[10]]
            vFinal = self.tamPassosMUV/t 
            somaVelFinalMedia += vFinal

            #calcula tempo médio total 
            # no experimento a parada era no décimo terceiro passo
            tTotal = self.dataX[peaks[12]] - self.dataX[peaks[0]] 
            somaTTotalMedio += tTotal """
        
        self.addTempoMUV()
        self.addPassosMUV()
        self.addTamPassosMUV()

        """ velFinalMedia = somaVelFinalMedia/5
        tTotalMedio = somaTTotalMedio/5
        acelMedia = velFinalMedia/tTotalMedio """

        #lista com o tamanho dos cortes pra calcular o corte médio
        """ soma = [0]

        for i in range(5):
            soma += yCaminhada[i]

        yCaminhadaMedia = (soma / 5)

        #plota caminhada media
        fig, ax = plt.subplots()
        plt.plot(yCaminhadaMedia)
        plt.title('Caminhada Média')
        ax.set_xlabel('Tempo (segundos)')
        ax.set_ylabel('Resultante (forca g)')
        plt.show() """

        self.ids.graph.remove_widget(self.graficoPos)
        self.ids.graph.remove_widget(self.graficoVel)

        self.analticoPlot.points = [(0,0)]
        self.eulerPlot.points = [(0,0)]
        self.velPlot.points = [(0,0)]


        dt = 0.1
        tf = self.tempoTotalMUV

        a = 1
        v = 0
        t = 0
        posicaoA = 0
        posicaoE = 0

        while (t < tf):
            self.analticoPlot.points.append((t,posicaoA))
            self.eulerPlot.points.append((t,posicaoE))
            self.velPlot.points.append((t,v))

            v = self.velocidadeMUV(a, v, dt)
            posicaoA = self.posicaoAnaliticoMUV(v, dt, a, t)
            posicaoE = self.posicaoEulerMUV(posicaoE, v, dt,t)
            t += dt

        yMaxV = v
        if(posicaoA > posicaoE):
            yMaxPos = posicaoA
        else:
            yMaxPos = posicaoE
        
        self.graficoPos = Graph(xmin=0, xmax=t, ymin=0, ymax=yMaxPos,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                draw_border=True,xlabel='Tempo (s)',ylabel='Espaço (m)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)

        self.graficoPos.add_plot(self.analticoPlot)
        self.graficoPos.add_plot(self.eulerPlot)
        self.ids.graph.add_widget(self.graficoPos)
        
        print(v)
        self.graficoVel = Graph(xmin=0, xmax=t, ymin=0, ymax = yMaxV,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                draw_border=True,xlabel='Tempo (s)',ylabel='Velocidade (m/s)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)

        self.graficoVel.add_plot(self.velPlot)
        self.ids.graph.add_widget(self.graficoVel)

class QuedaLivreScreen(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.telaQuedaLivre = QuedaLivre();

        self.add_widget(self.telaQuedaLivre)

    def on_pre_enter(self):
        Window.bind(on_keyboard=self.voltar)

    def voltar(self,window,key,*args):
        if key == 27:
            App.get_running_app().root.current = 'menuPlota'
            return True

    def on_pre_leave(self):
        Window.unbind(on_keyboard=self.voltar)

class QuedaLivre(BoxLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.graph_theme = {
            'label_options':{
                'color':[0,0,0,1]
            }
        }
        self.graficoPos = Graph(xmin=0, xmax=1, ymin=0, ymax=10,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                x_grid=True, y_grid=True,
                                draw_border=True,xlabel='Tempo (s)',ylabel='Espaço (m)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)
        
        self.analticoPlot = MeshLinePlot(color=[1,0,0,1])
        self.analticoPlot.points = [(0,0)]
        self.eulerPlot = MeshLinePlot(color=[0,1,0,1])
        self.eulerPlot.points = [(0,0)]

        self.ids.graph.add_widget(self.graficoPos)
        self.graficoPos.add_plot(self.analticoPlot)
        self.graficoPos.add_plot(self.eulerPlot)

        self.graficoVel = Graph(xmin=0, xmax=1, ymin=0, ymax=10,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                x_grid=True, y_grid=True,
                                draw_border=True,xlabel='Tempo (s)',ylabel='Velocidade (m/s)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)

        self.velPlot = MeshLinePlot(color=[1,0,0,1])
        self.velPlot.points = [(0,0)]

        self.ids.graph.add_widget(self.graficoVel)
        self.graficoVel.add_plot(self.velPlot)

        self.graficoAcel = Graph(xmin=0, xmax=1, ymin=0, ymax=10,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                x_grid=True, y_grid=True,
                                draw_border=True,xlabel='Tempo (s)',ylabel='Aceleração (m/s^2)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 1,
                                y_grid_label=True,
                                **self.graph_theme)

        self.acelPlot = MeshLinePlot(color=[1,0,0,1])
        self.acelPlot.points = [(0,0)]

        self.ids.graph.add_widget(self.graficoAcel)
        self.graficoAcel.add_plot(self.acelPlot)

    def addTempoQuedaLivre(self):
        self.tempoTotalQuedaLivre = (float)(self.ids.tempoQuedaLivre.text)

    def addAlturaQuedaLivre(self):
        self.alturaTotalQuedaLivre = (float)(self.ids.alturaQuedaLivre.text)

    def addTamPassosQuedaLivre(self):
        self.tamPassosQuedaLivre = self.ids.tamPassosQuedaLivre.text

    def g(self):
        return 9.80665

    def velocidadeAnaliticaQL(self, v0, t):
        m = 0.8
        k = 4.1
        e = 2.7182

        exp = -1*((k*t)/m)
        micro = e ** exp
        a = m*self.g()/k
        b = -a

        return (a + (v0+b)*micro)

    def posicaoAnaliticoQL(self, v0, t):
        return (v0*t +(self.g()*t*t)/2)

    def posicaoEulerQL(self, y0, v0, t):
        m = 0.8
        k = 4.1

        v = self.g()+v0-(v0*k/m)
        return (y0 + v*t/2)

    def gerarGraficoQuedaLivre(self):
        
        """ self.dataX, self.dataY, self.dataZ, self.dataG = Physics.returnVector(self)

        if(self.dataX == 0):
            return 
        else:
            p = Aviso3()
            p.open() """

        # variáveis
        posicaoA = 0
        posicaoE = 0
        v = 0
        t = 0
        tf = 0
        tQuedaSoma = 0
        dt = 0.1
        soma = 0
        #params = [1, 1, x]
        vxa = []
        xa = []
        xe = []
        aceleracao = []
        zoomAntes = []
        zoomDepois = []
        tSoltura = 0
        tParada = 0
        xQueda = []
        yQueda = []
        yQuedaMedio = []
        yQuedaIsolada = []

        """ # criação do gráfico
        fig, ax = plt.subplots()
        plt.plot(x,y)
        plt.title('Dados do acelerometro')
        ax.set_xlabel('Tempo (segundos)')
        ax.set_ylabel('Resultante (forca g)')
        plt.show()

        # procura picos
        peaks, _ = find_peaks(y, distance=150, height=12)


        for i in range(5):
            # isola as quedas do grafico
            zoomAntes = peaks[i]-800
            zoomDepois = peaks[i]+500
            xQueda.append(data[zoomAntes:zoomDepois,0])
            yQueda.append(data[zoomAntes:zoomDepois,4])
        

            # isola somente o instante da queda
            index = 0
            for j in yQueda[i]:
                index +=1
                if(j < 0.9):
                    tSoltura = data[index + zoomAntes, 0]
                    tParada = data[peaks[i]-18,0]

                    tQuedaSoma = tQuedaSoma + (tParada - tSoltura)

                    x1 = data[index+zoomAntes:peaks[i] - 18, 0]
                    y1 = data[index+zoomAntes:peaks[i] - 18, 4]

                    break

        soma = [0]

        for i in range(5):
            soma = soma + yQueda[i]

        yQuedaMedio = (soma/5) 

        for i in range(5):
            fig, ax = plt.subplots()
            plt.plot(xQueda[0]-21.495595721,yQueda[i]) #ajuste pro tempo de começo do exp
            plt.title(f'Queda Isolada {i+1}')
            ax.set_xlabel('Tempo (segundos)')
            ax.set_ylabel('Resultante (forca g)')
            plt.show()

        fig, ax = plt.subplots()
        plt.plot(xQueda[0]-21.495595721,yQuedaMedio) #ajuste pro tempo de começo da gravação
        plt.title('Queda Média')
        ax.set_xlabel('Tempo (segundos)')
        ax.set_ylabel('Resultante (forca g)')
        plt.show()

        f = 0
        for i in range(5):
            f = f + np.average(yQueda[i])

        f = f/5 """
        self.addTempoQuedaLivre()
        self.addAlturaQuedaLivre()

        self.ids.graph.remove_widget(self.graficoPos)
        self.ids.graph.remove_widget(self.graficoVel)
        #self.ids.graph.remove_widget(self.graficoAcel)

        self.analticoPlot.points = [(0,0)]
        self.eulerPlot.points = [(0,0)]
        self.velPlot.points = [(0,0)]
        self.acelPlot.points = [(0,0)]



        #tQuedaMedio = tQuedaSoma / 5
        tf = self.tempoTotalQuedaLivre

        while(t < tf):
            posicaoA = self.posicaoAnaliticoQL(v, t)
            posicaoE = self.posicaoEulerQL(posicaoE, v, t)
            v = self.velocidadeAnaliticaQL(v, t)
            self.analticoPlot.points.append((t,posicaoA))
            self.eulerPlot.points.append((t,posicaoE))
            self.velPlot.points.append((t,v))

            t += dt

        yMaxV = v
        if(posicaoA > posicaoE):
            yMaxPos = posicaoA
        else:
            yMaxPos = posicaoE
        
        self.graficoPos = Graph(xmin=0, xmax=t-dt, ymin=0, ymax=yMaxPos,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                draw_border=True,xlabel='Tempo (s)',ylabel='Espaço (m)',
                                x_grid_label=True, x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 4,
                                y_grid_label=True,
                                **self.graph_theme)

        self.graficoPos.add_plot(self.analticoPlot)
        self.graficoPos.add_plot(self.eulerPlot)
        self.ids.graph.add_widget(self.graficoPos)
        
        self.graficoVel = Graph(xmin=0, xmax=t-dt, ymin=0, ymax = yMaxV * 1.1,  
                                border_color=[0, 0, 0, .4],
                                background_color = [1,1,1,1],
                                draw_border=True,xlabel='Tempo (s)',ylabel='Velocidade (m/s)',
                                x_grid_label=True,x_ticks_minor = 1,x_ticks_major = 1,
                                y_ticks_minor = 1,y_ticks_major = 2,
                                y_grid_label=True,
                                **self.graph_theme)

        self.graficoVel.add_plot(self.velPlot)
        self.ids.graph.add_widget(self.graficoVel)

# POPUP
class Aviso1(Popup):
    pass

class Aviso2(Popup):
    print("tchau")
    pass

class Aviso3(Popup):
    pass

class main(App):
    def build(self):
        return Gerenciador()

main().run()