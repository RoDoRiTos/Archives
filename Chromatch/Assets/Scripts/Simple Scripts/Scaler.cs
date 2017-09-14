using UnityEngine;
using System.Collections;

public class Scaler : MonoBehaviour {

  private float _scale = 0.5f;

  private bool _reachedMax = false;

	void Update () {
    Vector3 scale = new Vector3(_scale, _scale, _scale);

    transform.localScale = scale;

    if (!_reachedMax) {
      _scale += 0.005f;
    }
    else /*_reachedMax*/ {
      _scale -= 0.005f;
    }

    if(_scale > 1.0f) {
      _reachedMax = true;
    }

    if (_scale < 0.10f) {
      Destroy(gameObject);
    }
	}
}
