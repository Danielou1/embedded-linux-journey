# --- Configuration par défaut (PC / x86) ---
CXX = g++
TARGET = security_check_pc

# --- Règle par défaut (quand tu tapes juste 'make') ---
all:
	$(CXX) security_check.cpp -o $(TARGET)

# --- Règle pour ARM (quand tu tapes 'make arm') ---
# Ici, on change le compilateur et le nom du fichier de sortie
arm: CXX = arm-linux-gnueabihf-g++
arm: TARGET = security_check_arm
arm: all

# --- Nettoyage ---
clean:
	rm -f security_check_pc security_check_arm
