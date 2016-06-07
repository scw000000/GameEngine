// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9.pypp.hpp"

namespace bp = boost::python;

struct ConstBaseIterator_less__std_scope_vector_less__CEGUI_scope_Scheme_scope_LoadableUIElement__greater__comma__CEGUI_scope_Scheme_scope_LoadableUIElement__greater__wrapper : CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >, bp::wrapper< CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > > {

    ConstBaseIterator_less__std_scope_vector_less__CEGUI_scope_Scheme_scope_LoadableUIElement__greater__comma__CEGUI_scope_Scheme_scope_LoadableUIElement__greater__wrapper( )
    : CEGUI::ConstBaseIterator<std::vector<CEGUI::Scheme::LoadableUIElement, std::allocator<CEGUI::Scheme::LoadableUIElement> >, CEGUI::Scheme::LoadableUIElement>( )
      , bp::wrapper< CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > >(){
        // null constructor
    
    }

    virtual ::CEGUI::Scheme::LoadableUIElement getCurrentValue(  ) const {
        bp::override func_getCurrentValue = this->get_override( "getCurrentValue" );
        return func_getCurrentValue(  );
    }

};

void register_ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_class(){

    { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >
        typedef bp::class_< ConstBaseIterator_less__std_scope_vector_less__CEGUI_scope_Scheme_scope_LoadableUIElement__greater__comma__CEGUI_scope_Scheme_scope_LoadableUIElement__greater__wrapper, boost::noncopyable > ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer_t;
        ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer_t ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer = ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer_t( "ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9", bp::no_init );
        bp::scope ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_scope( ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer );
        ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( bp::init< >("*************************************************************************\n\
           No default construction available\n\
        *************************************************************************\n") );
        { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::getCurrentValue
        
            typedef CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > exported_class_t;
            typedef ::CEGUI::Scheme::LoadableUIElement ( exported_class_t::*getCurrentValue_function_type )(  ) const;
            
            ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( 
                "getCurrentValue"
                , bp::pure_virtual( getCurrentValue_function_type(&::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::getCurrentValue) )
                , "*!\n\
            \n\
               Return the value for the item at the current iterator position.\n\
            *\n" );
        
        }
        { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::isAtEnd
        
            typedef CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > exported_class_t;
            typedef bool ( exported_class_t::*isAtEnd_function_type )(  ) const;
            
            ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( 
                "isAtEnd"
                , isAtEnd_function_type( &::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::isAtEnd )
                , "*!\n\
            \n\
               Return whether the current iterator position is at the end of the iterators range.\n\
            *\n" );
        
        }
        { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::isAtStart
        
            typedef CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > exported_class_t;
            typedef bool ( exported_class_t::*isAtStart_function_type )(  ) const;
            
            ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( 
                "isAtStart"
                , isAtStart_function_type( &::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::isAtStart )
                , "*!\n\
            \n\
               Return whether the current iterator position is at the start of the iterators range.\n\
            *\n" );
        
        }
        ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( bp::self != bp::self );
        { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::operator=
        
            typedef CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > exported_class_t;
            typedef ::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > & ( exported_class_t::*assign_function_type )( ::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > const & ) ;
            
            ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( 
                "assign"
                , assign_function_type( &::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::operator= )
                , ( bp::arg("rhs") )
                , bp::return_self< >()
                , "*!\n\
            \n\
               ConstBaseIterator assignment operator\n\
            *\n" );
        
        }
        ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( bp::self == bp::self );
        { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::toEnd
        
            typedef CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > exported_class_t;
            typedef void ( exported_class_t::*toEnd_function_type )(  ) ;
            
            ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( 
                "toEnd"
                , toEnd_function_type( &::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::toEnd )
                , "*!\n\
            \n\
               Set the iterator current position to the end position.\n\
            *\n" );
        
        }
        { //::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::toStart
        
            typedef CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement > exported_class_t;
            typedef void ( exported_class_t::*toStart_function_type )(  ) ;
            
            ConstBaseIterator_78cd23dcc51d261e1f508a899854e1a9_exposer.def( 
                "toStart"
                , toStart_function_type( &::CEGUI::ConstBaseIterator< std::vector< CEGUI::Scheme::LoadableUIElement >, CEGUI::Scheme::LoadableUIElement >::toStart )
                , "*!\n\
            \n\
               Set the iterator current position to the start position.\n\
            *\n" );
        
        }
    }

}