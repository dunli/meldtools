
#ifndef VM_RULE_HPP
#define VM_RULE_HPP

#include <string>
#include <vector>
#include <ostream>

#include "conf.hpp"
#include "vm/defs.hpp"
#include "vm/predicate.hpp"

namespace vm
{

class rule
{
   private:

      rule_id id;
      //linker  
      size_t linker_id;
      std::string str;
      byte_code code;
		code_size_t code_size;
		typedef std::vector<predicate*> predicate_vector;
      predicate_vector predicates;
      predicate_vector dependency_list;  
      bool is_persistent;

   public:
	
		void print(std::ostream&, const vm::program * const) const;
		
      inline rule_id get_id(void) const { return id; }
		inline const std::string get_string(void) const { return str; }

      inline void add_predicate(predicate *p) { predicates.push_back(p); }
      inline void set_bytecode(code_size_t _size, byte_code _code) {
			code_size = _size;
			code = _code;
		}
		
      inline code_size_t get_codesize(void) const { return code_size; }
		inline byte_code get_bytecode(void) const { return code; }
		inline size_t num_predicates(void) const { return predicates.size(); }

      inline void set_as_persistent(void) { is_persistent = true; }
      inline bool as_persistent(void) const { return is_persistent; }

		typedef predicate_vector::const_iterator predicate_iterator;
		inline predicate_iterator begin_predicates(void) const { return predicates.begin(); }
		inline predicate_iterator end_predicates(void) const { return predicates.end(); }
        inline predicate *get_predicate_number(size_t i) { return predicates[i]; }
    
      inline void add_dependency(predicate* p) { dependency_list.push_back(p); }
      inline predicate* get_dependency(size_t i) { return dependency_list[i]; }          
      
      inline void  set_linker_id(size_t id) { linker_id = id ; }
      inline size_t get_linker_id(void) const { return linker_id; }


      explicit rule(const rule_id _id, const std::string& _str):
         id(_id), str(_str), is_persistent(false) { }

		~rule(void) { delete []code; }
};

}

#endif
