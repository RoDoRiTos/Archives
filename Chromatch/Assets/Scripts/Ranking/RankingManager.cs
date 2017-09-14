using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class RankingManager : MonoBehaviour {

  private RankingData _rankData;

  private Transform _changePanel;
  private Transform _timePanel;

  private Text _countFirstPlace;
  private Text _countSecondPlace;
  private Text _countThirdPlace;

  private Text _timeFirstPlace;
  private Text _timeSecondPlace;
  private Text _timeThirdPlace;

  void Start () {
    _changePanel = transform.Find("Change Count Panel");
    _timePanel = transform.Find("Time Count Panel");

    _countFirstPlace = _changePanel.Find("Change Count Rank Text").Find("1st Text").GetComponent<Text>();
    _countSecondPlace = _changePanel.Find("Change Count Rank Text").Find("2nd Text").GetComponent<Text>();
    _countThirdPlace = _changePanel.Find("Change Count Rank Text").Find("3rd Text").GetComponent<Text>();

    _timeFirstPlace = _timePanel.Find("Time Count Rank Text").Find("1st Text").GetComponent<Text>();
    _timeSecondPlace = _timePanel.Find("Time Count Rank Text").Find("2nd Text").GetComponent<Text>();
    _timeThirdPlace = _timePanel.Find("Time Count Rank Text").Find("3rd Text").GetComponent<Text>();
  }

	void Update () {
    _countFirstPlace.text = "1st: " + _rankData.changeCount[0].ToString() + " Changes";
    _countSecondPlace.text = "2nd: " + _rankData.changeCount[1].ToString() + " Changes";
    _countThirdPlace.text = "3rd: " + _rankData.changeCount[2].ToString() + " Changes";

    _timeFirstPlace.text = "1st: " + _rankData.timeCount[0].ToString() + " Seconds";
    _timeSecondPlace.text = "2nd: " + _rankData.timeCount[1].ToString() + " Seconds";
    _timeThirdPlace.text = "3rd: " + _rankData.timeCount[2].ToString() + " Seconds";
  }

  public void LoadEasy() {
    _rankData = GetComponent<FileManager>().ReadRanking("easyRank");
  }

  public void LoadMed() {
    _rankData = GetComponent<FileManager>().ReadRanking("medRank");
  }

  public void LoadHard() {
    _rankData = GetComponent<FileManager>().ReadRanking("hardRank");
  }
}
