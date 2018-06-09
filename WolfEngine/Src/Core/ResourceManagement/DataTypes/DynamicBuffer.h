#pragma once

#include "..\..\Logger.h"

template <typename T>
struct DynamicBuffer {
public:
	DynamicBuffer() {
		m_buffer = NULL;
		m_len = 0;
		m_capacity = 2;
	}
	~DynamicBuffer() {
		if (m_len > 0)
			free(m_buffer);
		m_capacity = m_len = 0;
	}

	T& operator[](const u32& i) {
		return m_buffer[i];
	}
	T operator[](const u32& i) const{
		return m_buffer[i];
	}

	const T& operator=(const T& rhs) {
		this->m_len = rhs.m_len;
		this->m_capacity = rhs.m_capacity;

		Clear(this->m_buffer);
		memcpy(this->m_buffer, rhs.m_buffer, m_len);
		
		return *this;
	}


	void PushFront(const T& data) {
		if (m_len > 0) {
			m_len++;
			if (m_len > m_capacity) 
				AllocMem();
			
			memmove(&m_buffer[1], m_buffer, (m_len - 1) * sizeof(T));
			m_buffer[0] = data;
		}
		else {
			m_len++;
			m_capacity++;
			m_buffer = (T*)malloc(m_capacity * sizeof(T));
			m_buffer[m_len - 1] = data;
		}
	}

	void PopFront() {
		if (m_len > 1) {
			m_len--;
			memmove(&m_buffer[0], &m_buffer[1], (m_len) * sizeof(T));

			if ((float)(m_len*1.2f) < m_capacity)
				FreeMem();
		}
		else if (m_len == 1)
			Clear();
		else
			OutputErrorMsg("DynamicBuffer", ERR_MALLOC, "Can't pop data. The DynamicBuffer have a size of 0.");
	}

	void PushBack(const T& data) {
		if (m_len > 0) {
			m_len++;
			if (m_len >= m_capacity) 
				AllocMem();
			
			m_buffer[m_len - 1] = data;
		}
		else {
			m_len++;
			m_capacity++;
			m_buffer = (T*)malloc(m_capacity * sizeof(T));
			m_buffer[m_len - 1] = data;
		}
	}

	void PopBack() {
		if (m_len > 1) {
			m_len--;
			if ((float)(m_len*1.2f) < m_capacity)
				FreeMem();
		}
		else if (m_len == 1)
			Clear();
		else
			OutputErrorMsg("DynamicBuffer", ERR_MALLOC, "Can't pop back data. The DynamicBuffer have a size of 0.");
	}

	void Clear() {
		if (m_len > 0) {
			m_len = 0;
			m_capacity = 2;
			free(m_buffer);
		}
	}

	const u32 Length() const{
		return m_len;
	}
	const size_t Size() const{
		return m_len * sizeof(T);
	}
private:
	void AllocMem() {
		m_capacity *= 1.5f;
		
		T *tmp_buffer = NULL;
		tmp_buffer = (T*)realloc(m_buffer, m_capacity * sizeof(T));
		if (tmp_buffer)
			m_buffer = tmp_buffer;
		else
			OutputErrorMsg("DynamicBuffer", ERR_MALLOC, "Failed to reallocate memory.");
	}
	void FreeMem() {
		m_capacity /= 1.2f;

		T *tmp_buffer = NULL;
		tmp_buffer = (T*)realloc(m_buffer, m_capacity * sizeof(T));
		if (tmp_buffer)
			m_buffer = tmp_buffer;
		else
			OutputErrorMsg("DynamicBuffer", ERR_MALLOC, "Failed to free memory.");
	}

	T *m_buffer;
	u32 m_len;
	float m_capacity;
};