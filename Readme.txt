1.  k20emul ; 최초 K20에 F411보드를 붙여서 QMK 올림 
              - custom key & LED
              - 3731 LED Matrix

2. k20emul2 ; F072에서 I2C동작을 안하여 따로 만들어 테스트 함 - 이게 최종
                 - 디지털엔코더 추가

3.  tauchef ; durgod 프로젝트를 그대로 복사하여 테스트하고
                - 컴파일 후 elf파일이 안만들어져서 4번을 만들어 테스트
                - LED를 동작시키는데 안되어 2번으로 한참 연구
                - k310 LED 동작완료 최종
                
4.  tauchef2 ; K310 LED 동작완료 (계속 개발중)
                 led애니메이션 역스텝함수, 마우스, 다이나믹 매크로, 매트릭스led에 스테터스led제어, 
          10/31 -> 윈모드-맥모드, 맥키 추가, Via에서 layer 변경에러 수정
                 
terrazzo ; terrazzo를 K20에 이식하여 동작을 검토함

8. K310 ; 

9. K310 led

10. k310rgb_F401_err_23050427 ; durgod K310RGB 
                (F401에서 컴파일시 dynamic memory error발생 --> F072로 변경 필요함

11. k310rgb_F072_3731_230502 ; durgod K310RGB 3731 LED Driver를 복수로 사용해 RGB구현

12. k310rgb_gpio변경전_230516 ; 

13. k310rgb_pulsar_dev ; durgod K310RGB, 거의 최종샘플, 개발 완료 
                       string RGB LED를 점퍼로 장착 (펄사 대응하여 21개 추가)
                       OLED도 점퍼로 장착
                       디지털 엔코더 점퍼로 장착
                       펄사 대응 3개 키 추가
                       smart hub 점퍼연결 연동

14. k310rgb  ; durgod K310RGB기구에 맞게 PCB 자체제작, 
                                string RGB LED, OLED, Encoder, KM switch B/D연결

15. pulsar_cnc ; 13번에서 파생, Pulsar cnc tenkeyless 제품 
                (KM switch B/D, 21개 더미LED, 3개키 추가, 디지탈 엔코더, no OLED)

 QMK ver0.21.6 적용 ==> projectName_v0216
 QMK ver0.22.2 적용 ==> projectName_v0222

16. pulsar/xboard ; durgod/pulsar_cnc_v0216을 복사
                    v0.22.2 적용 / PID를 "Pulsar Xboard"로 변경, VIA json파일도 같이 변경

17. 모두 v0.23.0적용예정(KM스위치 허브장착모델은 chibios.c파일을 수정해야 함)
     reMAP은 VIA용 json파일을 적용하여 바로 사용가능
     signal RGB는 코드를 그대로 make하여 별로 펌웨어로 만듬 (이 펌웨어는 VIA, reMAP, Signal RGB 모두 사용가능, 동시는 아님)

       vial은 검토 중
                     


----------------------------------------------------------------------------------------------

< Metable Vender ID = 0x1C6C >
< Device ID >
METABLE K310       = 0xF010
METABLE K310 LED = 0xF011
K310RGB Metable_Pulsar Develope = 0xF012
METABLE K310 RGB = 0xF013 (230710)
Pulsar CNC = 0xF014(230711)

METABLE K30 RGB = 0xF020		(1 encoder)
METABLE K20 RGB = 0xF021           (waycos에서 개발했던것 2 encoder)

METABLE Designer T11 RGB = 0xF030  (Delux 한손키보드, 1 encoder, oled)
METABLE Designer T12 RGB = 0xF032  (Delux 한손키보드, no encoder)
