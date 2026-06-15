
// ex02 = identifier le vrai type avec dynamic_cast
#pragma once

class Base {
	public:
		// destructeur VIRTUEL : c'est ce qui rend la classe polymorphique
		// sans methode virtuelle pas de vtable / pas de RTTI => dynamic_cast compilerait pas
		// virtuel aussi pour pouvoir delete un Base* qui pointe vers A/B/C sans leak
		virtual ~Base(void);
};
