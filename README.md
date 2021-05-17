# ScooterServer

토이 프로젝트로 개발중인 C++서버 입니다.
가능한 간단하게 구현하고 있습니다.

- POCO 라이브러리를 사용합니다.
- 패킷은 json 문자열로 이루어져있습니다.
  - Unity 클라이언트에서 TCP 통신을 위해 Telepathy 를 사용하여 4bytes의 헤더가 추가되었습니다.
- DBMS로 Sqlite를 사용합니다.
