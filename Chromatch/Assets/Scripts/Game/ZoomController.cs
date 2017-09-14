using UnityEngine;
using System.Collections;

public class ZoomController : MonoBehaviour
{

	void Start ()
	{
	
	}
	
	void Update ()
	{
		Vector2 scrollDelta = Input.mouseScrollDelta;
		transform.Translate (0, 0, scrollDelta.y);
		UpdateZoomLimit ();
	}

	private void UpdateZoomLimit ()
	{
		Vector3 pos = transform.position;
		if (pos.z > -10.0f) {
			transform.position = new Vector3 (0, 0, -10.0f);
		} else if (pos.z < -125.0f) {
			transform.position = new Vector3 (0, 0, -125.0f);
		}
	}
}
