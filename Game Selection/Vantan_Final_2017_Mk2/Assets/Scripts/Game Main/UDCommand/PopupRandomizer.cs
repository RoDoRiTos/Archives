using UnityEngine;
using System.Collections;

namespace UDCommand {
  public class PopupRandomizer : MonoBehaviour {

    [SerializeField]
    GameObject[] popups = null;

    int currentPop = 0;

    private void Awake() {
      gameObject.SetActive(false);
    }

    public void Animate() {
      popups[currentPop].transform.parent.localPosition = new Vector3(Random.Range(-900.0f, 700.0f), Random.Range(-500.0f, 300.0f));
      popups[currentPop].GetComponent<Animator>().Play("Flicker");
      currentPop++;
      if (currentPop > popups.Length - 1) {
        currentPop = 0;
      }
    }
  }
}
