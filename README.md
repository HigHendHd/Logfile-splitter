# Logfile-splitter

Spaltet zu große Logfiles auf mehrere auf.

Das Projekt beinhaltet einen Loggenerator um ein Testlog zu erzeugen und einen Logsplitter der die eigentliche Arbeit macht.

## Logfile-splitter kompilieren

### Unter Linux

**Benötigte Programme**

 - gcc
 - make
 - mingw32-gcc

Git repository herunterladen

̀̀```
git clone https://github.com/HigHendHd/Logfile-splitter.git
```

In das Verzeichnis wechseln und bin Ordner erstellen

```
cd Logfile-splitter
mkdir bin
```

Sources kompilieren

```
make # Um für Linux und Windows zu kompilieren
make linux # Um nur Linux Binaries zu kompilieren
make windows # Um nur Windows Binaries zu kompilieren
```

Die Binaries können auch wieder vom System entfernt werden

```
make clean
```
