# 01 – Linux Basics for Embedded Developers

Welcome to the foundation of your **Embedded Linux Journey**.
Unlike standard Linux usage, embedded development requires a deep understanding of how the kernel interacts with hardware, how the filesystem is structured, and how to manage limited resources.

---

## 🎯 Learning Objectives

1.  **The Root Filesystem (RootFS)**: Understanding standard directories (`/bin`, `/etc`, `/var`) and virtual filesystems (`/proc`, `/sys`, `/dev`).
2.  **Permissions & Security**: Managing users, groups, and executable rights (`chmod`, `chown`).
3.  **Process Management**: Monitoring and controlling system tasks (`top`, `ps`, `kill`).
4.  **IO Redirection**: Handling Standard Input, Output, and Error streams (Crucial for logging).

---

## 📚 1. The Virtual Filesystem (The "Magic" folders)

In Linux, **"Everything is a file"**. This is especially true in embedded systems where hardware pins, logs, and kernel settings are accessed as files.

| Directory | Description | Embedded Context |
| :--- | :--- | :--- |
| **`/dev`** | Device Nodes | Contains files representing hardware (e.g., `/dev/ttyUSB0` for UART, `/dev/sda` for storage). |
| **`/proc`** | Process Info | Virtual interface to the kernel. `/proc/cpuinfo` tells you about the processor. |
| **`/sys`** | Sysfs | Exposes kernel objects. Used to toggle GPIOs or read sensors (e.g., `/sys/class/gpio`). |
| **`/etc`** | Configuration | Startup scripts, network config (`/etc/network/interfaces`), and hostnames live here. |

### 📝 Exercise
Run these commands to inspect your current system (WSL):
```bash
cat /proc/cpuinfo        # View CPU details
ls -l /dev/tty*          # List terminal devices
df -h                    # Check disk usage
```

---

## 🔐 2. Permissions & Ownership

Embedded devices often run as `root`, but secure applications should use specific users.

- **`chmod`**: Change mode (read/write/execute).
  - `chmod +x script.sh`: Make a script executable.
  - `chmod 600 secret.key`: Read/Write only for the owner.
- **`chown`**: Change owner.
  - `chown root:root file`: Assign file to root user and group.
- **`sudo`**: Execute with administrative privileges.

---

## ⚙️ 3. Process Management

You need to know if your application crashed, is using too much RAM, or needs to be stopped.

| Command | Action |
| :--- | :--- |
| `ps aux` | Lists all running processes with details. |
| `top` / `htop` | Real-time system monitoring (CPU/RAM usage). |
| `kill -9 <PID>` | Forcefully stops a process with ID `<PID>`. |
| `dmesg` | **Critical:** Prints kernel ring buffer logs. Best way to see hardware errors. |

---

## 🔄 4. Streams & Redirection

Embedded apps often run in the background (headless). You must capture their output.

- `>` : Redirect output to a file (overwrite).
- `>>` : Append output to a file.
- `2>` : Redirect **errors** only.
- `|` (Pipe) : Pass the output of one command as input to another.

**Example:**
```bash
# Find all "usb" entries in kernel logs and save to a file
dmesg | grep "usb" > usb_logs.txt
```

---

## 🚀 Next Steps

Move to the `cheatsheet_embedded.md` in this folder for a quick reference of commands you will use daily.

---
*© 2026 Embedded Linux Journey*
