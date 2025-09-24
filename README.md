# 🌱 Sistema de Irrigação Automatizada com Arduino

Um sistema inteligente que monitoriza a humidade do solo e o nível de água para automatizar a rega de plantas, com alertas visuais e sonoros.

## 📋 Funcionalidades

- **Rega Automática**: Ativa a bomba quando o solo está seco e há água disponível
- **Monitorização em Tempo Real**: Mede humidade, nível de água e intensidade luminosa
- **Sistema de Alertas Inteligente**: 
  - Alerta sonoro (buzzer) durante o dia
  - Alerta visual (LED piscante) durante a noite
- **Display LCD**: Mostra informações do sistema
- **Controlo por Botão**: Alterna entre diferentes ecrãs no display

## 🛠️ Componentes Utilizados

| Componente | Quantidade | Função |
|------------|------------|--------|
| Arduino Uno | 1 | Controlador principal |
| Sensor de Humidade do Solo | 1 | Mede a humidade da terra |
| Sensor de Nível de Água | 1 | Monitoriza o depósito |
| Sensor LDR | 1 | Detecta se é dia/noite |
| Display LCD I2C | 1 | Mostra informações |
| Servo Motor | 1 | Simula a bomba de água |
| Buzzer | 1 | Alerta sonoro |
| LED | 1 | Alerta visual |
| Botão | 1 | Controla o display |

## 🔌 Esquema de Ligações

### Diagrama do Circuito (Tinkercad)
<img src="https://github.com/user-attachments/assets/9592eecb-935d-4939-b527-44e3dd0008a9" alt="Diagrama do Circuito no Tinkercad" width="500" />

### Back to life
<img src="https://github.com/user-attachments/assets/4e75a642-2823-4824-9695-4a9ef86c6d78" alt="Montagem Física do Projeto" width="500" />
