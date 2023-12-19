# Semester Aufgabe 2023 Uni Augsburg

## Aufgabe

### Systembeschreibung A: Minesweeper
Es soll das Spiel Minesweeper1 implementiert werden, das ausschließlich auf der Kommandozeile gespielt wird. Dabei sollen die folgenden Aspekte beru ̈cksichtigt werden:

• Die Gro ̈ße des Spielfeldes soll mit Hilfe von Kommandozeilenparametern bestimmt werden. Gibt der Benutzer keine Kommandozeilenparameter fu ̈r die Gro ̈ße des Spielfeldes an, soll eine sinnvolle Standardgro ̈ße fu ̈r das Feld genutzt werden.

• Das Feld soll u ̈bersichtlich auf Kommandozeile ausgegeben werden. Dabei soll deutlich erkennbar sein, welche Positionen im Feld bereits aufgedeckt sind und welche nicht.

• Mithilfe von Benutzereingaben soll es dem Benutzer mo ̈glich sein, ein Feld aufzudecken, mit einer Flagge zu markieren oder eine solche Markierung von einem Feld zu entfernen.

• Mit Flaggen markierte Felder sollen nicht aufgedeckt werden ko ̈nnen.

• Am Ende des Spiels soll dem Benutzer angezeigt werden, wie viele Sekunden verstrichen sind und wie viele Befehle er gebraucht hat.

**Freiwillige Zusatzaufgaben**

Die Zeit und die Anzahl der Befehle soll in einer Textdatei gespeichert werden. Der Benutzer soll die Mo ̈glichkeit erhalten, sich anhand dieser Daten eine Bestenliste anzeigen zu lassen.

## Ideen

### Mögliche Aufbau des Spieles

    1. Spiel Feld Größe
        1.1 Beginner 8x8
        1.2 Intermediate 16x16
        1.3 Expert 30x16
        1.4 User -defined 
        >[!CAUTION]
        >MAX_ = x/y * 3 + 2
        
