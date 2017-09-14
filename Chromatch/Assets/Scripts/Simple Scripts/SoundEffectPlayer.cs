using UnityEngine;
using System.Collections;

public class SoundEffectPlayer : MonoBehaviour {

  [SerializeField]
  private AudioClip _se1 = null;
  [SerializeField]
  private AudioClip _se2 = null;
  [SerializeField]
  private AudioClip _se3 = null;

  private AudioSource _source;

  void Start () {
    _source = GetComponent<AudioSource>();
	}
	
	public void PlaySE1() {
    if (_se1 == null) {
      Debug.Log("SE 1 Not Loaded");
      return;
    }

    _source.PlayOneShot(_se1, 1.0f);
  }

  public void PlaySE2() {
    if (_se2 == null) {
      Debug.Log("SE 2 Not Loaded");
      return;
    }

    _source.PlayOneShot(_se2, 1.0f);
  }

  public void PlaySE3() {
    if (_se3 == null) {
      Debug.Log("SE 3 Not Loaded");
      return;
    }

    _source.PlayOneShot(_se3, 1.0f);
  }

}
