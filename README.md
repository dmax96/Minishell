Minishell

**As beautiful as a shell**

Questo progetto consiste nella creazione di un semplice shell, una versione minimalista di bash.

## 🛠️ **Funzionalità Principali**

La shell implementa le seguenti funzionalità:

- **Prompt interattivo**: Mostra un prompt quando è in attesa di un nuovo comando.
- **History**: Gestisce una history dei comandi inseriti.
- **Esecuzione di comandi**: Cerca e avvia l'eseguibile corretto (basato sulla variabile `PATH` o usando un percorso relativo/assoluto).
- **Gestione delle variabili d'ambiente**: Espande le variabili d'ambiente (es. `$HOME`) e gestisce `$?` per lo stato di uscita dell'ultimo comando eseguito.
- **Redirezioni**: Supporta le redirezioni di input/output (`<`, `>`, `<<`, `>>`).
- **Pipe**: Implementa i pipe (`|`) per collegare l'output di un comando all'input del successivo.
- **Quote**: Gestisce le singole (`'`) e doppie (`"`) quote per evitare l'interpretazione dei meta-caratteri.
- **Segnali**: Gestisce i segnali `ctrl-C`, `ctrl-D` e `ctrl-\` come in bash.
- **Built-in commands**: Implementa i comandi built-in:
  - `echo` con l'opzione `-n`
  - `cd` con percorso relativo o assoluto
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## 📂 **Struttura del Progetto**

- **Linguaggio**: Il progetto è scritto in C.
- **Makefile**: Deve contenere le regole `$(NAME)`, `all`, `clean`, `fclean` e `re`.

## 📝 **Come Testare**

1. Clona la repository:
   ```bash
   git clone https://github.com/dmax96/minishell.git
   ```
2. Compila il progetto:
   ```bash
   make
   ```
3. Esegui il shell:
   ```bash
   ./minishell
   ```
