
# vbus Workspace (Windows MVP)

This MVP creates a **virtual Ethernet hub** and a **virtual CAN bus**, a daemon (`vbusd.exe`), a CLI (`vbusctl.exe`), a recorder (`.vbuscap`), and a simple **replay**.

Focus: Core mechanics and control path. **Shared-memory rings and real adapter bridges are stubbed** for later.

## Build

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

Run daemon:
```powershell
build\Release\vbusd.exe
```

In another terminal use the CLI:
```powershell
build\Release\vbusctl.exe create eth0 eth 1000000000
build\Release\vbusctl.exe create can0 can 500000
build\Release\vbusctl.exe list
build\Release\vbusctl.exe record eth0 on logs\eth0.vbuscap
build\Release\vbusctl.exe send-eth eth0 deadbeefcafebabe
build\Release\vbusctl.exe stoprec eth0
build\Release\vbusctl.exe replay eth0 logs\eth0.vbuscap exact
```

> Hex payloads are for demo only. Real clients will use the shared-memory client API (`vbus_client`) in a later step.

## Named Pipe Control

- Pipe name: `\\.\pipe\vbusd`
- Line-oriented commands (space-separated). Responses are short text.

### Commands
- `create <busName> eth <link_bps>`
- `create <busName> can <bitrate>`
- `list`
- `record <busName> on <file>`
- `record <busName> off`
- `send-eth <busName> <hex-bytes>`
- `send-can <busName> <id> <hex-bytes>`
- `stoprec <busName>`
- `replay <busName> <file> <exact|burst|scale:K>`
- `quit`

## Roadmap

- Replace CLI send with **client shared memory** for data plane.
- Add **Npcap bridge** endpoint for real NICs.
- Implement bit timing and arbitration in `CanBus` and serialization delay in `EthHub`.
- Add **VLAN splitter tap**.
- Export **PCAPNG** in recorder for Ethernet.

