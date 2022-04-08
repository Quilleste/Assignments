#define u_int unsigned int

class patient {
	private:
		u_int id;
		float tglobulin;
		float msom_gen;
		float iglobulin_A;
		float iglobulin_M;
		float iglobulin_G;
		float imunCom;
		float lizocim;
		float actComp;
		u_int res;

	public:
		patient(u_int _id, float _tglobulin, float _msom_gen, float _iglobulin_A,
				float _iglobulin_M, float _iglobulin_G, float _imunCom,
				float _lizocim, float _actComp, u_int _res) {
			id = _id;
			tglobulin = _tglobulin;
			msom_gen = _msom_gen;
			iglobulin_A = _iglobulin_A;
			iglobulin_M = _iglobulin_M;
			iglobulin_G = _iglobulin_G;
			imunCom = _imunCom;
			lizocim = _lizocim;
			actComp = _actComp;
			res = _res;
		}

		u_int getId() {
			return id;
		}

		float getTglobulin() {
			return tglobulin;
		}

		float getMsom_gen() {
			return msom_gen;
		}

		float getIglobulin_A() {
			return iglobulin_A;
		}

		float getIglobulin_M() {
			return iglobulin_M;
		}

		float getIglobulin_G() {
			return iglobulin_G;
		}

		float getImunCom() {
			return imunCom;
		}

		float getLizocim() {
			return lizocim;
		}

		float getActComp() {
			return actComp;
		}

		u_int getRes() {
        	return res;
		}
};
