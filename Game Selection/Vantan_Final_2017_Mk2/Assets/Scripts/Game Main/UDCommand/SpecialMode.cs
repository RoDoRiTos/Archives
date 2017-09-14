using UnityEngine;
using System.Collections;

namespace UDCommand {
  public static class SpecialModeData {
    private static int time;

    public static int Time {
      get { return time; }
      set { time = value; }
    }
  }

  public class SpecialMode : MonoBehaviour {

    float currentTime;
    int buttonCount;

    bool[] buttonDown = new bool[8];
    bool animInit = false;
    bool endSEPlayed = false;

    [SerializeField]
    private GameObject resultCanvas = null;

    [SerializeField]
    private GameObject instructText = null;

    [SerializeField]
    private GameObject textAnim = null;

    [SerializeField]
    private GameObject popupRand = null;

    private GameObject trans;

    void Start() {
      if (SpecialModeData.Time < 5) {
        currentTime = 5;
      }
      else if (SpecialModeData.Time > 20) {
        currentTime = 20;
      }
      else {
        currentTime = SpecialModeData.Time;
      }
      SoundMgr.SoundLoadBgm("SpecialBGM", "UDCommand/SpecialBGM");
      SoundMgr.SoundLoadSe("SpecialSE", "UDCommand/SpecialSE");
      SoundMgr.SoundLoadSe("UDCGameEnd", "UDCommand/Finish");
      SoundMgr.SoundLoadSe("UDCDecide", "UDCommand/Decide");

      if (SoundMgr.isBgmPlaying("SpecialBGM") == 0) {
        SoundMgr.PlayBgm("SpecialBGM",0.3f);
      }

      trans = GameObject.FindGameObjectWithTag("Transition Handler");

      instructText.SetActive(true);
      resultCanvas.SetActive(false);
      textAnim.SetActive(false);
    }

    void Update() {
      if (currentTime > 0) {
        GetInputs();
      }

      if (buttonCount > 0 && !animInit) {
        gameObject.GetComponentInChildren<Animator>().Play("Wiggle");
        animInit = true;
        textAnim.SetActive(true);
        popupRand.SetActive(true);
      }

      if (currentTime > 0 && buttonCount > 0) {
        currentTime -= Time.deltaTime;
      }

      if (currentTime <= 0) {
        gameObject.GetComponentInChildren<Animator>().Play("PopupSpecial");
        instructText.SetActive(false);
        resultCanvas.SetActive(true);
        if (!endSEPlayed) {
          SoundMgr.PlaySe("UDCGameEnd");
          endSEPlayed = true;
          textAnim.GetComponent<TextAnimation>().Reset();
          textAnim.SetActive(false);
        }
        SoundMgr.StopBgm();
      }

      if (resultCanvas.activeSelf == true) {
        var selector = resultCanvas.GetComponent<MSMM.MenuSelector>();
        var index = selector.GetCurrentSelectedIndex();
        if(index == 0) {
          if (Input.GetAxis("BottomGreen") == 1) {
            if (UDCommand.SelectedGameMode.GetMode() == (int)UDCommand.GameMode.Trial) {
              MSMM.RankingTempData.TempScore += (uint)buttonCount * 1;
              SoundMgr.PlaySe("UDCDecide");
              selector.Reset();
              trans.GetComponent<MSMM.Transition>().LoadScene("UDCTrialResult");
              MSMM.PlayCounter.AddCount(MSMM.CountType.UDCEnd);
            }
            else if (UDCommand.SelectedGameMode.GetMode() == (int)UDCommand.GameMode.Challenge) {
              MSMM.RankingTempData.TempScore += (uint)buttonCount * 1;
              SoundMgr.PlaySe("UDCDecide");
              selector.Reset();
              trans.GetComponent<MSMM.Transition>().LoadScene("UDCChallengeResult");
              MSMM.PlayCounter.AddCount(MSMM.CountType.UDCEnd);
            }
          }
        }
      }
    }

    private void GetInputs() {
      if (Input.GetAxis("BottomRed") == 1 && !buttonDown[0]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 1);
        buttonDown[0] = true;
      }
      else if(Input.GetAxis("BottomRed") == 0) {
        buttonDown[0] = false;
      }

      if (Input.GetAxis("BottomGreen") == 1 && !buttonDown[1]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 2);
        buttonDown[1] = true;
      }
      else if (Input.GetAxis("BottomGreen") == 0) {
        buttonDown[1] = false;
      }

      if (Input.GetAxis("BottomBlue") == 1 && !buttonDown[2]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 3);
        buttonDown[2] = true;
      }
      else if (Input.GetAxis("BottomBlue") == 0) {
        buttonDown[2] = false;
      }

      if (Input.GetAxis("BottomYellow") == 1 && !buttonDown[3]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 4);
        buttonDown[3] = true;
      }
      else if (Input.GetAxis("BottomYellow") == 0) {
        buttonDown[3] = false;
      }

      if (Input.GetAxis("UpperRed") == 1 && !buttonDown[4]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 1);
        buttonDown[4] = true;
      }
      else if (Input.GetAxis("UpperRed") == 0) {
        buttonDown[4] = false;
      }

      if (Input.GetAxis("UpperGreen") == 1 && !buttonDown[5]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 2);
        buttonDown[5] = true;
      }
      else if (Input.GetAxis("UpperGreen") == 0) {
        buttonDown[5] = false;
      }

      if (Input.GetAxis("UpperBlue") == 1 && !buttonDown[6]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 3);
        buttonDown[6] = true;
      }
      else if (Input.GetAxis("UpperBlue") == 0) {
        buttonDown[6] = false;
      }

      if (Input.GetAxis("UpperYellow") == 1 && !buttonDown[7]) {
        buttonCount++;
        popupRand.GetComponent<PopupRandomizer>().Animate();
        SoundMgr.PlaySe("SpecialSE", 4);
        buttonDown[7] = true;
      }
      else if (Input.GetAxis("UpperYellow") == 0) {
        buttonDown[7] = false;
      }
    }
  }
}
