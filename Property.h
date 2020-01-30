/*********************************************************/
/*  (%T% %S%), %J% <$A$> <$2.126$>                       */
/*  (%W% 02/12/2019 ) Escrito                            */
/*  (%X% 05/12/2019 ) Añadido _buildJob                  */
/*  (%X% 05/12/2019 ) Añadido ejecución administrativa   */
/*  (%X% 06/12/2019 ) Añadido _buildManifest             */
/*  (%X% 06/12/2019 ) Añadido _buildRc                   */
/*  (%M% 06/12/2019 )                                    */
/*  (%M% 08/12/2019 ) Se añade multicreación             */
/*         o sea, creación de varios a la vez            */
/*  (%M% 17/12/2019 ) Se añade CMakeList.txt             */
/*  (%M% 10/01/2020 ) Se añade _buildGo                  */
/*  (%M% 25/01/2020 ) Se añade QProperty                 */
/*  <$Válido$>                                           */
/*********************************************************/

#ifndef __PROPERTY_H
# define __PROPERTY_H

/*
 * Define las propiedades que tienen los objetos.
 * Son Variables, ReadOnly y Constantes, debe ponerse en el parámetro 'en' como un entero.
 *
 * En casos de Constantes debe el parámetro 'pSet' ser nullptr.
 */
template <typename TCont, typename T, int en>
    class QProperty {
public:
    using _TSet = void (TCont::*)(T);
    using _TGet = T (TCont::*)() const;
    //typedef void (TCont::* _TSet)(T);
    //typedef T (TCont::* _TGet)() const;

    enum TypeVariables { Variable = 0x0000, ReadOnly = 0x0001, Constant = 0x0002 };
    QProperty() : _object(nullptr), _set(nullptr), _get(nullptr)   {}
    QProperty(TCont *Object, T (TCont::*pGet)() const, void (TCont::*pSet)(T) /* if pSet == CONSTANT será nullptr*/): _object(Object), _set(pSet), _get(pGet) {}

    //-- Sobrecarga el signo '=' para dar valor a la propiedad usando el miembro set
    inline T operator =(const T& value)  {
      if(en == static_cast<int>(QProperty::Constant))
        return value;

      if(!_flag)
        (_object->*_set)(value);

      if(en == static_cast<int>(QProperty::ReadOnly))
        _flag = static_cast<bool>(en);

      return value;
    }
    //-- Para hacer posible castear la clase de la propiedad al tipo interno
    inline operator T() const {
        return (_object->*_get)();
    }
private:
    bool _flag = false;
    TCont* _object;  //-- Puntero al módulo que contiene la propiedad
    _TSet _set;    //void (TCont::*_set)(T);        //-- Puntero a la función set
    _TGet _get;    //T (TCont::*_get)() const;      //-- Puntero a la función get
};

#endif // __PROPERTY_H
