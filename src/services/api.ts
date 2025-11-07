import { Book, User, ReadingListItem, FilterOptions } from '@/types/book';

/**
 * API Service - Mock implementation
 * Replace these functions with actual API calls to your C++ backend
 * 
 * Expected C++ Backend Endpoints:
 * - POST /api/auth/login
 * - POST /api/auth/register
 * - GET /api/books
 * - GET /api/books/filter
 * - GET /api/books/:id
 * - GET /api/reading-list/:userId
 * - POST /api/reading-list
 * - DELETE /api/reading-list/:bookId
 */

const API_BASE_URL = 'http://localhost:8080/api'; // Update with your C++ backend URL

// Mock data for development
const mockBooks: Book[] = [
  {
    id: '1',
    title: 'The Great Gatsby',
    author: 'F. Scott Fitzgerald',
    description: 'A classic American novel set in the Jazz Age that explores themes of wealth, love, and the American Dream.',
    coverImage: 'https://images.unsplash.com/photo-1543002588-bfa74002ed7e?w=400&h=600&fit=crop',
    year: 1925,
    genre: ['Fiction', 'Classic'],
    isbn: '9780743273565',
    rating: 4.5
  },
  {
    id: '2',
    title: '1984',
    author: 'George Orwell',
    description: 'A dystopian social science fiction novel and cautionary tale about the dangers of totalitarianism.',
    coverImage: 'https://images.unsplash.com/photo-1495446815901-a7297e633e8d?w=400&h=600&fit=crop',
    year: 1949,
    genre: ['Fiction', 'Dystopian', 'Science Fiction'],
    isbn: '9780451524935',
    rating: 4.7
  },
  {
    id: '3',
    title: 'To Kill a Mockingbird',
    author: 'Harper Lee',
    description: 'A gripping tale of racial injustice and childhood innocence in the American South.',
    coverImage: 'https://images.unsplash.com/photo-1544947950-fa07a98d237f?w=400&h=600&fit=crop',
    year: 1960,
    genre: ['Fiction', 'Classic'],
    isbn: '9780061120084',
    rating: 4.8
  },
];

export const authAPI = {
  login: async (email: string, password: string): Promise<User> => {
    // TODO: Replace with actual C++ backend call
    // const response = await fetch(`${API_BASE_URL}/auth/login`, {
    //   method: 'POST',
    //   headers: { 'Content-Type': 'application/json' },
    //   body: JSON.stringify({ email, password })
    // });
    
    // Mock implementation
    await new Promise(resolve => setTimeout(resolve, 1000));
    return {
      id: '1',
      email,
      name: email.split('@')[0]
    };
  },

  register: async (email: string, password: string, name: string): Promise<User> => {
    // TODO: Replace with actual C++ backend call
    await new Promise(resolve => setTimeout(resolve, 1000));
    return {
      id: '1',
      email,
      name
    };
  },

  logout: async (): Promise<void> => {
    // TODO: Replace with actual C++ backend call
    await new Promise(resolve => setTimeout(resolve, 500));
  }
};

export const booksAPI = {
  getAll: async (): Promise<Book[]> => {
    // TODO: Replace with actual C++ backend call
    // const response = await fetch(`${API_BASE_URL}/books`);
    // return await response.json();
    
    await new Promise(resolve => setTimeout(resolve, 800));
    return mockBooks;
  },

  filter: async (filters: FilterOptions): Promise<Book[]> => {
    // TODO: Replace with actual C++ backend call
    // const query = new URLSearchParams(filters as any).toString();
    // const response = await fetch(`${API_BASE_URL}/books/filter?${query}`);
    // return await response.json();
    
    await new Promise(resolve => setTimeout(resolve, 800));
    let filtered = [...mockBooks];

    if (filters.author) {
      filtered = filtered.filter(book => 
        book.author.toLowerCase().includes(filters.author!.toLowerCase())
      );
    }

    if (filters.year) {
      filtered = filtered.filter(book => book.year >= filters.year!);
    }

    if (filters.genre) {
      filtered = filtered.filter(book => 
        book.genre.some(g => g.toLowerCase() === filters.genre!.toLowerCase())
      );
    }

    if (filters.prompt) {
      // In real implementation, this would use AI/NLP in C++ backend
      filtered = filtered.filter(book => 
        book.title.toLowerCase().includes(filters.prompt!.toLowerCase()) ||
        book.description.toLowerCase().includes(filters.prompt!.toLowerCase())
      );
    }

    return filtered;
  },

  getById: async (id: string): Promise<Book | null> => {
    // TODO: Replace with actual C++ backend call
    await new Promise(resolve => setTimeout(resolve, 500));
    return mockBooks.find(book => book.id === id) || null;
  }
};

export const readingListAPI = {
  get: async (userId: string): Promise<(Book & { status: string })[]> => {
    // TODO: Replace with actual C++ backend call
    await new Promise(resolve => setTimeout(resolve, 600));
    return mockBooks.slice(0, 2).map(book => ({
      ...book,
      status: 'want-to-read'
    }));
  },

  add: async (userId: string, bookId: string, status: string): Promise<void> => {
    // TODO: Replace with actual C++ backend call
    await new Promise(resolve => setTimeout(resolve, 500));
  },

  remove: async (userId: string, bookId: string): Promise<void> => {
    // TODO: Replace with actual C++ backend call
    await new Promise(resolve => setTimeout(resolve, 500));
  }
};
