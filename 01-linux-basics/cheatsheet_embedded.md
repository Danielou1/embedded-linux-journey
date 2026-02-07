# 🛠️ Embedded Linux Commands Cheatsheet

A curated list of commands frequently used when debugging hardware and kernel issues.

## 🔍 Hardware Inspection

| Command | Usage |
| :--- | :--- |
| `dmesg -w` | Follow kernel logs in real-time (great for plugging/unplugging devices). |
| `lsmod` | List currently loaded kernel modules (drivers). |
| `modprobe <module>` | Load a kernel module manually. |
| `lsusb` | List connected USB devices (ID and Name). |
| `lspci` | List PCI devices. |
| `lscpu` | detailed CPU architecture info. |
| `free -h` | Show available RAM. |

## 🌐 Network & Connectivity

| Command | Usage |
| :--- | :--- |
| `ip a` | Show IP addresses (replacing obsolete `ifconfig`). |
| `ip route` | Show routing table. |
| `ping -c 4 8.8.8.8` | Check internet connectivity. |
| `ss -tuln` | Show open ports (listening services). |

## 📂 Filesystem & Storage

| Command | Usage |
| :--- | :--- |
| `df -h` | Disk usage summary. |
| `du -sh *` | Size of current directory contents. |
| `mount | grep sd` | Check mounted drives. |
| `sync` | **Important:** Force write from RAM to disk (prevents corruption before power cut). |

## ⚡ System Control

| Command | Usage |
| :--- | :--- |
| `shutdown -h now` | Safe power off. |
| `reboot` | Restart system. |
| `systemctl status <service>` | Check status of a background service (systemd). |
| `journalctl -xe` | View detailed system logs for errors. |

---
*Tip: Combine commands with grep! E.g., `dmesg | grep tty` finds serial ports.*
