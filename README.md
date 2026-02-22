# Delivery-drone-system
## 프로젝트 개요
본 프로젝트는 배달 비용 절감과, 배달이 불가능한 위치에 대한 불편함 해소를 목표로 하였습니다.

기존 배달 시스템은, 이륜차 혹은 사륜차를 기반으로 서비스를 제공하다보니, 한강처럼 일부 진입 금지 지역과 산과 같이 높은 지역에는 배달이 제한되었습니다.
이를 해결하고자, 자동차의 이동성을 넘어서는 배달용 드론을 구현하였습니다.

## 개발 목표
- 오랜 시간 비행가능한 드론 기체 설계 
- 최소 과일 하나 이상 운송이 가능하도록 드론 하중 설계
- 착륙장 인식 알고리즘 설계 및 제작
- GPS 기반 배달 드론 시스템 완성

## 시스템 구성
### 하드웨어 구성
- 드론 센서들 및 모터 구동 제어용 보드 [Jetson nano, Jetson mega, Jetson Giga]
- 착륙장 인식용 camera
- 가속도 자이로 센서[MPU6050]
- 드론 전자속도 컨트롤러[ESC]
- 드론 수신용 리시버

### 소프트웨어 구성
- 비행 자세 제어 시스템
- GPS 데이터 수집 및 피드백
- 착륙장 인식 알고리즘 설계

## 본인 담당 역할 및 구현 역량

### 담당 범위
메인 비행 제어 펌웨어 및 RC 수신기 펌웨어 전체를 설계하고 구현하였습니다.

### 주요 구현 내용 (Kuro_Dron.ino)
- **3축 독립 PID 제어기 구현**: X/Y/Z 축 각각의 비례(P)·적분(I)·미분(D) 이득 파라미터 설계 및 조정, 자세 안정화 루프 구성
- **5모드 FSM 설계**: `fly_mode` 기반 비활성(0) / 수동 RC(1) / 자율비행(2) / 자동 이륙(3) / 자동 착륙(4) 상태 전환 논리 구현
- **MPU9250 IMU 연동**: I2C `Wire` 라이브러리로 9축 가속도·자이로·지자기 데이터 수집 및 자세 추정 처리
- **GPS 데이터 파싱**: `TinyGPS++` 라이브러리 연동, `Serial2`(9600 baud)로 GPS 위치 정보 실시간 수신 및 위치 피드백 루프 구성
- **ESC 4채널 서보 출력**: 모터 캘리브레이션 루틴 구현 (2000μs 최대 신호 → 5초 대기 → 분리)

### 주요 구현 내용 (Kuro_Dron_RadioReceiver.ino)
- **5채널 PWM 신호 읽기**: 아날로그 핀(A0/A1/A5/A4/A3)으로 RC 수신기 700~2000μs PWM 신호 읽기 및 범위 검증
- **시리얼 인코딩 프로토콜 설계**: `(char)(Receiver_vals[i] / 5 + 52)` 변환으로 수신기 값을 ASCII 문자로 압축 인코딩, 메인 보드로 Serial 전송
- **수신기 초기화 확인**: 채널4 신호 유효성 검증 후 연결 확인(`'c'` 출력) 핸드셰이크 로직

### 핵심 기술 판단
- 드론-수신기 간 통신을 직접 정의한 커스텀 인코딩 프로토콜 채택: 표준 라이브러리 미지원 환경(Arduino Giga)에서의 호환성 확보
- 모터 캘리브레이션을 이륙 전 필수 루틴으로 설계: 모터 출력 편차 최소화 시도

## 기체 설계
### 회로도
<img width="1976" height="1346" alt="드론 회로도_ALTools_AIUpscaler" src="https://github.com/user-attachments/assets/bacd6901-990b-4f3e-b612-90db7b6e7250" />

- Brokking.net 회로도 참고

### 3D 모델
<img width="1824" height="1434" alt="드론 3D 모델링1_ALTools_AIUpscaler" src="https://github.com/user-attachments/assets/69c09189-e31e-4a08-a54b-f26ee5597be2" />
<img width="1824" height="1434" alt="드론 3D 모델링2" src="https://github.com/user-attachments/assets/576ce455-7b53-4440-a673-3b3d395f517d" />

- Fusion360을 이용하여 드론 기체 설계

### 기체 구현

<img width="2912" height="2298" alt="드론 구현1" src="https://github.com/user-attachments/assets/21471af5-763f-4bec-b1bd-a16057cfea55" />
<img width="4000" height="3000" alt="드론 구현2" src="https://github.com/user-attachments/assets/81fb3dda-0e76-4bf9-be0c-ca29237af403" />
<img width="4032" height="3024" alt="드론 구현3" src="https://github.com/user-attachments/assets/2210793f-1503-4430-b4ad-6e240d7f7073" />

## 프로젝트 결론
### 실험 결과 요약
- 드론 기체 구현 성공, 비행 테스트 실행
- 비행 자세 제어 불가 현상과 기체 Flip 현상 발생
- 캘리브레이션 값 저장 불가
### 분석 및 한계
- 비행 시 기체 모터들의 출력 차이와 초당 각 모터의 출력 변화폭이 매우 큼  
- Arduino Giga 보드로 사용이 불가능한 라이브러리 존재
- IMU MEMS Sensor(MPU-6050)가 진동에 매우 취약
### 향후 개선 방향
- MPU-9250(9축 기울기 센서)로 교체
- 전원 켤 때마다 캘리브레이션 진행
- Arduino Giga 보드에 맞게 라이브러리 파일 수정
### 프로젝트 의의
- 배달 사각지대(진입 제한 구역·고지대 등)를 드론 기반 배송으로 해결하려는 문제정의 및 시스템 제안
- Jetson 기반 영상처리와 센서/제어 하드웨어를 연동한 임베디드–제어–비전 통합 개발 경험 확보
- 과정에서 Flip/캘리브레이션 이슈 등 현실 운용 난제를 확인하고, 센서 교체·보정 방식 개선 등 구체적 개선 방향 도출
