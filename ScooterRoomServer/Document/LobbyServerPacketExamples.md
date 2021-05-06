# lobby server packet examples

- ReqLogin
```json
{ "packetGroup":0, "packetType":0, "accountId":100, "token":"dummy_token" }
```

- ReqRoomList
```json
{ "packetGroup":0, "packetType":1 }
```

- CreateRoom
```json
{ "packetGroup":0, "packetType":2 }
```

- EnterRoom
```json
{ "packetGroup":0, "packetType":3, "roomId":1 }
```