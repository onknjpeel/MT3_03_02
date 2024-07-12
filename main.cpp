#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <cmath>
#include <imgui.h>

const char kWindowTitle[] = "LC1B_06_オノ_ケンジピエール_タイトル";

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	result = {
		m1.m[0][0] + m2.m[0][0],m1.m[0][1] + m2.m[0][1],m1.m[0][2] + m2.m[0][2],m1.m[0][3] + m2.m[0][3],
		m1.m[1][0] + m2.m[1][0],m1.m[1][1] + m2.m[1][1],m1.m[1][2] + m2.m[1][2],m1.m[1][3] + m2.m[1][3],
		m1.m[2][0] + m2.m[2][0],m1.m[2][1] + m2.m[2][1],m1.m[2][2] + m2.m[2][2],m1.m[2][3] + m2.m[2][3],
		m1.m[3][0] + m2.m[3][0],m1.m[3][1] + m2.m[3][1],m1.m[3][2] + m2.m[3][2],m1.m[3][3] + m2.m[3][3]
	};
	return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	result = {
		m1.m[0][0] - m2.m[0][0],m1.m[0][1] - m2.m[0][1],m1.m[0][2] - m2.m[0][2],m1.m[0][3] - m2.m[0][3],
		m1.m[1][0] - m2.m[1][0],m1.m[1][1] - m2.m[1][1],m1.m[1][2] - m2.m[1][2],m1.m[1][3] - m2.m[1][3],
		m1.m[2][0] - m2.m[2][0],m1.m[2][1] - m2.m[2][1],m1.m[2][2] - m2.m[2][2],m1.m[2][3] - m2.m[2][3],
		m1.m[3][0] - m2.m[3][0],m1.m[3][1] - m2.m[3][1],m1.m[3][2] - m2.m[3][2],m1.m[3][3] - m2.m[3][3]
	};
	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 MakeRotateXMatrix(const Vector3& rotate) {
	Matrix4x4 rotateX;
	rotateX = {
		1,0,0,0,
		0,std::cos(rotate.x),std::sin(rotate.x),0,
		0,-std::sin(rotate.x),std::cos(rotate.x),0,
		0,0,0,1
	};
	return rotateX;
}

Matrix4x4 MakeRotateYMatrix(const Vector3& rotate) {
	Matrix4x4 rotateY;
	rotateY = {
		std::cos(rotate.y),0,-std::sin(rotate.y),0,
		0,1,0,0,
		std::sin(rotate.y),0,std::cos(rotate.y),
		0,0,0,0,1
	};
	return rotateY;
}

Matrix4x4 MakeRotateZMatrix(const Vector3& rotate) {
	Matrix4x4 rotateZ;
	rotateZ = {
		std::cos(rotate.z),std::sin(rotate.z),0,0,
		-std::sin(rotate.z),std::cos(rotate.z),0,0,
		0,0,1,0,
		0,0,0,1
	};
	return rotateZ;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return Multiply(1.0f / s, v); }
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

Vector3 operator-(const Vector3& v) { return { -v.x,-v.y,-v.z }; }
Vector3 operator+(const Vector3& v) { return v; }

Vector3& operator*=(Vector3& v, const float& s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	Vector3 &result = v;
	return result;
}

Vector3& operator-=(Vector3& v1, const Vector3& v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	Vector3 &result = v1;
	return result;
};

Vector3& operator+=(Vector3& v1, const Vector3& v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	Vector3 &result = v1;
	return result;
};

Vector3& operator/=(Vector3& v, const float& s) {
	v.x /= s;
	v.y /= s;
	v.z /= s;
	Vector3 &result = v;
	return result;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	const Vector3 a{ 0.2f,1.0f,0.0f };
	const Vector3 b{ 2.4f,3.1f,1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;

	const Matrix4x4 a4{ 2.0f,2.0f,2.0f,2.0f,
	2.0f, 2.0f, 2.0f, 2.0f,
	2.0f, 2.0f, 2.0f, 2.0f,
	2.0f, 2.0f, 2.0f, 2.0f };
	const Matrix4x4 b4{ 1.0f,1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f };
	Matrix4x4 c4 = a4 + b4;
	Matrix4x4 d4 = a4 - b4;

	const Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

	Vector3 f = -a;
	Vector3 g = +a;

	Vector3 h = { 2.0f,2.0f,2.0f };
	h *= 2.0f;
	Vector3 i = { 2.0f,2.0f,2.0f };
	i -= a;
	Vector3 j = { 2.0f,2.0f,2.0f };
	j += a;
	Vector3 k = { 2.0f,2.0f,2.0f };
	k /= 2.0f;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("Window");
		ImGui::Text("c:%f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d:%f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e:%f, %f, %f", e.x, e.y, e.z);
		ImGui::Text("matrix");
		ImGui::Text(
			"c4\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f",
			c4.m[0][0], c4.m[0][1], c4.m[0][2], c4.m[0][3],
			c4.m[1][0], c4.m[1][1], c4.m[1][2], c4.m[1][3],
			c4.m[2][0], c4.m[2][1], c4.m[2][2], c4.m[2][3],
			c4.m[3][0], c4.m[3][1], c4.m[3][2], c4.m[3][3]
		);
		ImGui::Text(
			"d4\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f",
			d4.m[0][0], d4.m[0][1], d4.m[0][2], d4.m[0][3],
			d4.m[1][0], d4.m[1][1], d4.m[1][2], d4.m[1][3],
			d4.m[2][0], d4.m[2][1], d4.m[2][2], d4.m[2][3],
			d4.m[3][0], d4.m[3][1], d4.m[3][2], d4.m[3][3]
		);
		ImGui::Text(
			"rotateMatrix\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]
		);
		ImGui::Text("f:%f, %f, %f", f.x, f.y, f.z);
		ImGui::Text("g:%f, %f, %f", g.x, g.y, g.z);
		ImGui::Text("h:%f, %f, %f", h.x, h.y, h.z);
		ImGui::Text("i:%f, %f, %f", i.x, i.y, i.z);
		ImGui::Text("j:%f, %f, %f", j.x, j.y, j.z);
		ImGui::Text("k:%f, %f, %f", k.x, k.y, k.z);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
