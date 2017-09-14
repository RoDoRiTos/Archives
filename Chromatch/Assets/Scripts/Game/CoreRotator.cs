using UnityEngine;
using System.Collections;

public class CoreRotator : MonoBehaviour {
	private Vector3 _lastFramePos = new Vector3(0,0,0);
	
	void Update () {
		if (Input.GetMouseButtonDown (0)) {
			_lastFramePos = Input.mousePosition;
		}
		if (Input.GetMouseButton (0)) {
			Vector3 mouseDelta = _lastFramePos - Input.mousePosition;
			transform.Rotate (Vector3.right,-mouseDelta.y,Space.World);
			transform.Rotate (Vector3.up,mouseDelta.x,Space.World);
			_lastFramePos = Input.mousePosition;
		}
	}
}
