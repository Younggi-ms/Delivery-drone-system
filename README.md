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

## 기체 설계
### 회로도
<img width="1976" height="1346" alt="드론 회로도_ALTools_AIUpscaler" src="https://github.com/user-attachments/assets/bacd6901-990b-4f3e-b612-90db7b6e7250" />

- Brokking.net 회로도 참고

### 3D 모델
<img width="1824" height="1434" alt="드론 3D 모델링1_ALTools_AIUpscaler" src="https://github.com/user-attachments/assets/69c09189-e31e-4a08-a54b-f26ee5597be2" />
<img width="1824" height="1434" alt="드론 3D 모델링2" src="https://github.com/user-attachments/assets/576ce455-7b53-4440-a673-3b3d395f517d" />

- Fusion360을 이용하여 드론 기체 설계





