export interface Book {
  id: string;
  title: string;
  author: string;
  description: string;
  coverImage: string;
  year: number;
  genre: string[];
  isbn: string;
  rating: number;
}

export interface User {
  id: string;
  email: string;
  name: string;
}

export interface ReadingListItem {
  bookId: string;
  addedAt: Date;
  status: 'want-to-read' | 'reading' | 'completed';
}

export interface FilterOptions {
  author?: string;
  year?: number;
  genre?: string;
  prompt?: string;
}
