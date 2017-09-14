using UnityEngine;
using System.Collections;

public class SceneSwitcher : MonoBehaviour {

  public void ChangeScene(string nextScene) {
    Application.LoadLevel(nextScene);
  }

}
